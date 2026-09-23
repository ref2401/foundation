<#
.SYNOPSIS
    Builds src/main.cpp into bin/<configuration>/unittests.exe using the MSVC compiler.

.PARAMETER Configuration
    Build configuration: Debug or Release. Defaults to Debug.

.PARAMETER Clean
    Removes the output directory for the selected configuration before building.

.EXAMPLE
    .\scripts\build_unittests.ps1 -Configuration Release
#>
[CmdletBinding()]
param(
    [Parameter(Position = 0)]
    [ValidateSet('Debug', 'Release')]
    [string] $Configuration = 'Debug',

    [switch] $Clean
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

# ---------------------------------------------------------------------------
# Layout: <root>/{src,scripts,bin}
# ---------------------------------------------------------------------------
$rootDir   = Split-Path -Parent $PSScriptRoot
$srcDir    = Join-Path $rootDir 'src'
$outDir    = Join-Path (Join-Path $rootDir 'bin') $Configuration.ToLowerInvariant()
$objDir    = Join-Path $outDir 'obj'
$ifcDir    = Join-Path $outDir 'ifc'          # compiled module interfaces (.ifc)
$asmDir    = Join-Path $outDir 'asm'          # /Fa assembly listings
$exeFile   = Join-Path $outDir 'unittests.exe'

if ($Clean -and (Test-Path -LiteralPath $outDir)) {
    Write-Host "Cleaning $Configuration -> $outDir" -ForegroundColor Cyan
    Remove-Item -LiteralPath $outDir -Recurse -Force
}

New-Item -ItemType Directory -Path $objDir -Force | Out-Null
New-Item -ItemType Directory -Path $ifcDir -Force | Out-Null
New-Item -ItemType Directory -Path $asmDir -Force | Out-Null

# ---------------------------------------------------------------------------
# Module interface units, listed by their path relative to src\ just like the
# .cpp sources below. cl.exe reads the module name out of the file itself and
# names the .ifc after it, so the script never needs to know that name -- which
# leaves the layout on disk free of any naming rule, partitions included.
#
# Order matters here, unlike for the sources: list a unit *after* every unit it
# imports, so an interface partition comes before the primary interface unit
# that re-exports it, and a module comes before anything that imports it.
# ---------------------------------------------------------------------------
$moduleNames = @(
    'foundation\core\core.api_types.ixx'
    'foundation\core\core.span.ixx'
    'foundation\core\core.ixx'
    'unittests\core\unittests.core.span.ixx'
    'unittests\core\unittests.core.ixx'
)

$modules = @(
    $moduleNames | ForEach-Object {
        $path = Join-Path $srcDir $_
        if (-not (Test-Path -LiteralPath $path)) {
            throw "Module '$_' listed in `$moduleNames but its file was not found: $path"
        }

        [pscustomobject]@{
            Name = $_
            Path = $path
            # Flatten the relative path into the .obj name so that two units
            # sharing a basename in different folders cannot overwrite each
            # other in the flat obj directory.
            Obj  = Join-Path $objDir (($_ -replace '\\', '-' -replace '\.ixx$', '') + '.obj')
        }
    }
)

# ---------------------------------------------------------------------------
# Non-module translation units: ordinary .cpp files that are compiled and
# linked in alongside the modules, listed by their path relative to src\.
# Order is irrelevant here -- unlike interface units, these have no build-order
# dependency on one another.
# ---------------------------------------------------------------------------
$sourceNames = @(
    'foundation\core\macros.cpp'
    'foundation\unittests.cpp'
    'unittests\main.cpp'
)

$sources = @(
    $sourceNames | ForEach-Object {
        $path = Join-Path $srcDir $_
        if (-not (Test-Path -LiteralPath $path)) {
            throw "Source '$_' listed in `$sourceNames but its file was not found: $path"
        }

        [pscustomobject]@{
            Name = $_
            Path = $path
            # Flatten the relative path into the .obj name so that two sources
            # sharing a basename in different folders cannot overwrite each
            # other in the flat obj directory.
            Obj  = Join-Path $objDir (($_ -replace '\\', '-' -replace '\.cpp$', '') + '.obj')
        }
    }
)

# ---------------------------------------------------------------------------
# Compiler / linker options
# ---------------------------------------------------------------------------
# Shared by both compile phases; /Fo and /Fe are supplied per phase.
# There is deliberately no /EH* option: the project is built without exceptions.
$compilerArgs = @(
    '/nologo'
    '/std:c++20'
    '/permissive-'
    '/utf-8'
    '/W4'
    '/WX-'
    '/diagnostics:caret'
    '/errorReport:prompt'

    # Language / codegen. Several of these are already the cl.exe default; they
    # are spelled out so the build never depends on a default changing.
    '/GR-'                  # no RTTI
    '/GS'                   # buffer security checks
    '/sdl'                  # additional security checks layered on /GS
    '/fp:precise'
    '/Gd'                   # __cdecl
    '/Zc:wchar_t'
    '/Zc:forScope'
    '/Zc:inline'            # drop unreferenced COMDATs (off by default)

    '/D_CRT_SECURE_NO_WARNINGS'
    '/DWIN32_LEAN_AND_MEAN'
    '/DNOMINMAX'
    '/DUNICODE'
    '/D_UNICODE'
    '/D_WINDOWS'

    "/I$srcDir"
    "/Fd:$objDir\unittests.pdb"
    "/Fa$asmDir\"           # assembly listings, one per translation unit
    '/FAsu'                 # ...with interleaved source, UTF-8 encoded
)

if ($Configuration -eq 'Debug') {
    # FND_DEBUG is the project's own switch, kept separate from the CRT's
    # _DEBUG: it is what turns FND_ASSERT into a real check rather than __noop.
    $compilerArgs += @('/Od', '/Zi', '/MDd', '/RTC1', '/D_DEBUG', '/DFND_DEBUG')
    $linkerArgs = @('/DEBUG')
}
else {
    # /Zi + /DEBUG so Release ships a PDB too; /OPT:REF and /OPT:ICF are what
    # keep the binary itself from paying for it.
    $compilerArgs += @('/O2', '/GL', '/Zi', '/MD', '/DNDEBUG')
    $linkerArgs = @('/DEBUG', '/LTCG', '/OPT:REF', '/OPT:ICF')
}

Write-Host "Building $Configuration -> $exeFile" -ForegroundColor Cyan

function Assert-CompileSucceeded {
    param([string] $What)

    if ($LASTEXITCODE -ne 0) {
        Write-Host "Build FAILED ($What, cl.exe exit code $LASTEXITCODE)" -ForegroundColor Red
        exit $LASTEXITCODE
    }
}


# ---------------------------------------------------------------------------
# Phase 1: compile each module interface unit to an .ifc (consumed by importers)
# plus an .obj (must be linked into the final executable). /interface covers the
# primary interface unit and interface partitions alike; cl.exe derives the .ifc
# name from the declaration inside the file, writing 'foundation.core:api_types'
# as foundation.core-api_types.ifc, which /ifcSearchDir then resolves on its own.
# ---------------------------------------------------------------------------
foreach ($module in $modules) {
    cl.exe @compilerArgs `
        '/c' `
        '/interface' `
        '/ifcOutput' "$ifcDir\" `
        '/ifcSearchDir' $ifcDir `
        "/Fo:$($module.Obj)" `
        "/TP" $module.Path

    Assert-CompileSucceeded "module $($module.Name)"
}

# ---------------------------------------------------------------------------
# Phase 2: compile the non-module translation units. They run after phase 1 and
# are given /ifcSearchDir, so a .cpp here is free to 'import foundation.core'
# as well as to #include a header.
# ---------------------------------------------------------------------------
foreach ($source in $sources) {
    cl.exe @compilerArgs `
        '/c' `
        '/ifcSearchDir' $ifcDir `
        "/Fo:$($source.Obj)" `
        $source.Path

    Assert-CompileSucceeded $source.Name
}

# ---------------------------------------------------------------------------
# Phase 3: compile main.cpp against those interfaces and link everything.
# ---------------------------------------------------------------------------
$moduleObjs = @($modules | ForEach-Object { $_.Obj })
$sourceObjs = @($sources | ForEach-Object { $_.Obj })

cl.exe @compilerArgs `
    '/ifcSearchDir' $ifcDir `
    "/Fo:$objDir\" `
    "/Fe:$exeFile" `
    @moduleObjs @sourceObjs `
    /link @linkerArgs
Assert-CompileSucceeded 'Link'

Write-Host "Build succeeded: $exeFile" -ForegroundColor Green
