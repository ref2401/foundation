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
$mainFile  = Join-Path $srcDir 'main.cpp'
$exeFile   = Join-Path $outDir 'unittests.exe'

if (-not (Test-Path -LiteralPath $mainFile)) {
    throw "Source file not found: $mainFile"
}

if ($Clean -and (Test-Path -LiteralPath $outDir)) {
    Write-Host "Cleaning $outDir" -ForegroundColor DarkGray
    Remove-Item -LiteralPath $outDir -Recurse -Force
}

New-Item -ItemType Directory -Path $objDir -Force | Out-Null

# ---------------------------------------------------------------------------
# Compiler / linker options
# ---------------------------------------------------------------------------
$compilerArgs = @(
    '/nologo'
    '/std:c++20'
    '/EHsc'
    '/W4'
    '/permissive-'
    '/utf-8'
    '/diagnostics:caret'
    "/I$srcDir"
    "/Fo:$objDir\"           # intermediate .obj files
    "/Fd:$objDir\unittests.pdb"
    "/Fe:$exeFile"
)

if ($Configuration -eq 'Debug') {
    $compilerArgs += @('/Od', '/Zi', '/MDd', '/RTC1', '/D_DEBUG')
    $linkerArgs = @('/DEBUG')
}
else {
    $compilerArgs += @('/O2', '/GL', '/MD', '/DNDEBUG')
    $linkerArgs = @('/LTCG', '/OPT:REF', '/OPT:ICF')
}

$sourceFiles = @($mainFile)

Write-Host "Building $Configuration -> $exeFile" -ForegroundColor Cyan

& cl.exe @compilerArgs @sourceFiles /link @linkerArgs
$exitCode = $LASTEXITCODE

if ($exitCode -ne 0) {
    Write-Host "Build FAILED (cl.exe exit code $exitCode)" -ForegroundColor Red
    exit $exitCode
}

Write-Host "Build succeeded: $exeFile" -ForegroundColor Green
