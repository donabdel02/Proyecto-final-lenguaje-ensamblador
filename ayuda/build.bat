@echo off
REM ============================================================
REM build.bat - Script de compilacion para BitQuest en Windows
REM Requiere: NASM y GCC de 64 bits en el PATH
REM ============================================================

echo.
echo  ============================================================
echo   BitQuest: Explorador de Matrices - Script de compilacion
echo  ============================================================
echo.

REM --- Verificar que NASM este disponible ---
where nasm >nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo  [ERROR] NASM no encontrado en el PATH.
    echo  Descargalo desde: https://www.nasm.us/
    pause
    exit /b 1
)

REM --- Verificar que GCC este disponible ---
where gcc >nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo  [ERROR] GCC no encontrado en el PATH.
    echo  Instala MinGW-w64 desde: https://www.mingw-w64.org/
    pause
    exit /b 1
)

echo  [1/3] Ensamblando rutinas.asm con NASM (win64)...
nasm -f win64 rutinas.asm -o rutinas.obj
if %ERRORLEVEL% neq 0 (
    echo  [ERROR] Fallo el ensamblado de rutinas.asm
    pause
    exit /b 1
)
echo       OK

echo  [2/3] Compilando main.c y juego.c con GCC...
gcc -Wall -Wextra -O2 -o BitQuest.exe main.c juego.c rutinas.obj
if %ERRORLEVEL% neq 0 (
    echo  [ERROR] Fallo la compilacion de C
    pause
    exit /b 1
)
echo       OK

echo  [3/3] Compilacion exitosa!
echo.
echo  ============================================================
echo   Ejecuta el juego con:  BitQuest.exe
echo  ============================================================
echo.
pause
