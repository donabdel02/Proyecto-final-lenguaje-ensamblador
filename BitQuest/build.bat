@echo off
echo Compilando BitQuest...

REM Ensamblar NASM
nasm -f win64 src/rutinas.asm -o src/rutinas.obj
if errorlevel 1 ( echo ERROR en rutinas.asm & pause & exit /b 1 )

REM Compilar archivos C
gcc -c src/juego.c  -o src/juego.obj  -I include
gcc -c src/mapas.c  -o src/mapas.obj  -I include
gcc -c src/main.c   -o src/main.obj   -I include

REM Enlazar todo
gcc src/main.obj src/juego.obj src/mapas.obj src/rutinas.obj ^
    -o BitQuest.exe -lkernel32

if errorlevel 1 ( echo ERROR al enlazar & pause & exit /b 1 )

echo Listo. Ejecuta BitQuest.exe
pause
