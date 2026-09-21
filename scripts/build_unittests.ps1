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
$compilerArgs = @(
    '/nologo'
    '/std:c++20'
    '/EHsc'
    '/W4'
    '/permissive-'
    '/utf-8'
    '/diagnostics:caret'
    "/I$srcDir"
    "/Fd:$objDir\unittests.pdb"
)

if ($Configuration -eq 'Debug') {
    $compilerArgs += @('/Od', '/Zi', '/MDd', '/RTC1', '/D_DEBUG')
    $linkerArgs = @('/DEBUG')
}
else {
    $compilerArgs += @('/O2', '/GL', '/MD', '/DNDEBUG')
    $linkerArgs = @('/LTCG', '/OPT:REF', '/OPT:ICF')
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
