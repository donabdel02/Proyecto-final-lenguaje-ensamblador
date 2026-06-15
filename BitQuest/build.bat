@echo off
echo Compilando BitQuest...

REM Ensamblar NASM
nasm -f win64 src/rutinas.nasm -o src/rutinas.obj
if errorlevel 1 ( echo ERROR en rutinas.nasm & pause & exit /b 1 )

REM Compilar archivos C
gcc -c src/jugador.c  -o src/jugador.obj  -I include
gcc -c src/mapas.c  -o src/mapas.obj  -I include
gcc -c src/renderizado.c  -o src/renderizado.obj  -I include
gcc -c src/objetos.c  -o src/objetos.obj  -I include
gcc -c src/main.c   -o src/main.obj   -I include

REM Enlazar todo
gcc src/main.obj src/jugador.obj src/mapas.obj src/renderizado.obj src/objetos.obj src/rutinas.obj ^
    -o BitQuest.exe -lkernel32 -lwinmm

if errorlevel 1 ( echo ERROR al enlazar & pause & exit /b 1 )

echo Listo. Ejecuta BitQuest.exe
pause
