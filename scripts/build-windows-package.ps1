param(
    [string]$JavaHome = ""
)

$ErrorActionPreference = "Stop"

$projectRoot = Resolve-Path (Join-Path $PSScriptRoot "..")
$cppDir = Join-Path $projectRoot "src\main\cpp"
$classesDir = Join-Path $projectRoot "target\classes"
$testClassesDir = Join-Path $projectRoot "target\test-classes"
$sourceList = Join-Path $projectRoot "target\java_sources.txt"
$testSourceList = Join-Path $projectRoot "target\test_sources.txt"
$jarPath = Join-Path $projectRoot "target\DimpleTradeApi-1.0.0.jar"
$jniDll = Join-Path $projectRoot "src\main\resources\win-x64\dimple_trade_jni.dll"

if ([string]::IsNullOrWhiteSpace($JavaHome)) {
    if (-not [string]::IsNullOrWhiteSpace($env:JAVA_HOME)) {
        $JavaHome = $env:JAVA_HOME
    } else {
        $JavaHome = "D:\myCodexSpace\ms-21.0.10\ms-21.0.10"
    }
}

if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
    throw "cmake is required to build dimple_trade_jni.dll, but it was not found in PATH."
}

if (-not (Test-Path (Join-Path $JavaHome "bin\javac.exe"))) {
    throw "JDK not found: $JavaHome"
}

Push-Location $cppDir
try {
    cmake -B build -S . -A x64
    cmake --build build --config Release
}
finally {
    Pop-Location
}

if (-not (Test-Path $jniDll)) {
    throw "Native JNI DLL was not copied to resources: $jniDll"
}

Remove-Item -Recurse -Force $classesDir,$testClassesDir -ErrorAction SilentlyContinue
New-Item -ItemType Directory -Force $classesDir,$testClassesDir | Out-Null

Get-ChildItem -Recurse -Filter *.java (Join-Path $projectRoot "src\main\java") |
    ForEach-Object { $_.FullName } |
    Out-File -Encoding ascii $sourceList

& (Join-Path $JavaHome "bin\javac.exe") --release 8 -encoding UTF-8 -d $classesDir "@$sourceList"
Copy-Item -Recurse -Force (Join-Path $projectRoot "src\main\resources\*") $classesDir

Get-ChildItem -Recurse -Filter *.java (Join-Path $projectRoot "src\test\java") |
    ForEach-Object { $_.FullName } |
    Out-File -Encoding ascii $testSourceList

& (Join-Path $JavaHome "bin\javac.exe") --release 8 -encoding UTF-8 -cp $classesDir -d $testClassesDir "@$testSourceList"
& (Join-Path $JavaHome "bin\java.exe") -cp "$classesDir;$testClassesDir" com.dimple.trade.KsdTradeApiWindowsResourceTest

& (Join-Path $JavaHome "bin\jar.exe") --create --file $jarPath -C $classesDir .
Write-Host "Built package: $jarPath"
