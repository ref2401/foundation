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
$mainFile  = Join-Path $srcDir 'main.cpp'
$exeFile   = Join-Path $outDir 'unittests.exe'

if (-not (Test-Path -LiteralPath $mainFile)) {
    throw "Source file not found: $mainFile"
}

if ($Clean -and (Test-Path -LiteralPath $outDir)) {
    Write-Host "Cleaning $Configuration -> $outDir" -ForegroundColor Cyan
    Remove-Item -LiteralPath $outDir -Recurse -Force
}

New-Item -ItemType Directory -Path $objDir -Force | Out-Null
New-Item -ItemType Directory -Path $ifcDir -Force | Out-Null
New-Item -ItemType Directory -Path $asmDir -Force | Out-Null

# ---------------------------------------------------------------------------
# Module interface units, in build order: list a module *after* every module it
# imports. A name maps to its source file by path, e.g.
# 'foundation.core' -> src\foundation\core.ixx
# ---------------------------------------------------------------------------
$moduleNames = @(
    'foundation.core'
)

$modules = @(
    $moduleNames | ForEach-Object {
        $path = Join-Path $srcDir (($_ -replace '\.', '\') + '.ixx')
        if (-not (Test-Path -LiteralPath $path)) {
            throw "Module '$_' listed in `$moduleNames but its source file was not found: $path"
        }

        [pscustomobject]@{
            Name = $_
            Path = $path
            Obj  = Join-Path $objDir "$_.obj"
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
    $compilerArgs += @('/Od', '/Zi', '/MDd', '/RTC1', '/D_DEBUG')
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
# plus an .obj (must be linked into the final executable).
# ---------------------------------------------------------------------------
foreach ($module in $modules) {
    Write-Host "  module $($module.Name)" -ForegroundColor DarkGray

    & cl.exe @compilerArgs `
        '/c' `
        '/interface' `
        '/ifcOutput' "$ifcDir\" `
        '/ifcSearchDir' $ifcDir `
        "/Fo:$($module.Obj)" `
        "/TP" $module.Path

    Assert-CompileSucceeded "module $($module.Name)"
}

# ---------------------------------------------------------------------------
# Publish the interfaces to bin\ifc, the directory .vscode\c_cpp_properties.json
# points IntelliSense at via /ifcSearchDir.
#
# cpptools holds a handle on every .ifc it resolves an 'import' against, so
# pointing it straight at bin\<config>\ifc makes cl.exe fail with C3474 the next
# time it rewrites one. Giving it its own copy keeps the two apart: a locked
# copy costs IntelliSense a window reload, never the build.
#
# Debug only -- the IntelliSense configuration defines _DEBUG, so Release
# interfaces would not match what the editor thinks it is compiling.
# ---------------------------------------------------------------------------
if ($Configuration -eq 'Debug') {
    $ideIfcDir = Join-Path (Join-Path $rootDir 'bin') 'ifc'
    New-Item -ItemType Directory -Path $ideIfcDir -Force | Out-Null

    $lockedIfcs = @()
    foreach ($ifc in Get-ChildItem -LiteralPath $ifcDir -Filter '*.ifc') {
        $copy = Join-Path $ideIfcDir $ifc.Name

        # cl.exe emits byte-identical interfaces for unchanged sources, so an
        # equal hash means the copy is already current and the lock is harmless.
        if (Test-Path -LiteralPath $copy) {
            $current = (Get-FileHash -LiteralPath $ifc.FullName -Algorithm SHA256).Hash
            if ($current -eq (Get-FileHash -LiteralPath $copy -Algorithm SHA256).Hash) {
                continue
            }
        }

        try {
            Copy-Item -LiteralPath $ifc.FullName -Destination $copy -Force -ErrorAction Stop
        }
        catch {
            $lockedIfcs += $ifc.Name
        }
    }

    if ($lockedIfcs.Count -gt 0) {
        Write-Host ("  {0} changed but IntelliSense is holding it - run 'Developer: Reload Window' to pick it up" -f ($lockedIfcs -join ', ')) -ForegroundColor Yellow
    }
}

# ---------------------------------------------------------------------------
# Phase 2: compile main.cpp against those interfaces and link everything.
# ---------------------------------------------------------------------------
$moduleObjs = @($modules | ForEach-Object { $_.Obj })

& cl.exe @compilerArgs `
    '/ifcSearchDir' $ifcDir `
    "/Fo:$objDir\" `
    "/Fe:$exeFile" `
    $mainFile @moduleObjs `
    /link @linkerArgs

Assert-CompileSucceeded 'main.cpp'

Write-Host "Build succeeded: $exeFile" -ForegroundColor Green
