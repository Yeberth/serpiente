@echo off
setlocal

set "PROJECT_DIR=%~dp0"
set "BUILD_DIR=%PROJECT_DIR%build-windows"

if not defined QT_PREFIX_PATH (
    echo Define QT_PREFIX_PATH con la ruta de Qt, por ejemplo:
    echo set QT_PREFIX_PATH=C:\Qt\5.15.2\msvc2019_64
    exit /b 1
)

where cmake >nul 2>&1
if errorlevel 1 (
    echo No se encontro CMake en PATH.
    exit /b 1
)

where windeployqt >nul 2>&1
if errorlevel 1 (
    echo No se encontro windeployqt en PATH.
    echo Agrega %%QT_PREFIX_PATH%%\bin al PATH o ejecuta este archivo desde un Qt Command Prompt.
    exit /b 1
)

cmake -S "%PROJECT_DIR%" -B "%BUILD_DIR%" ^
    -DCMAKE_PREFIX_PATH="%QT_PREFIX_PATH%" ^
    -DCMAKE_BUILD_TYPE=Release
if errorlevel 1 exit /b 1

cmake --build "%BUILD_DIR%" --config Release
if errorlevel 1 exit /b 1

windeployqt --release --multimedia ^
    "%BUILD_DIR%\Release\ventana_qt.exe"
if errorlevel 1 exit /b 1

echo.
echo Ejecutable creado:
echo %BUILD_DIR%\Release\ventana_qt.exe
exit /b 0
