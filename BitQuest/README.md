# BitQuest — Explorador de Matrices

Videojuego de consola en C y NASM de 64 bits.

## Cómo compilar y ejecutar

1. Instala [NASM](https://www.nasm.us/)
2. Instala [MinGW GCC](https://www.mingw-w64.org/)
3. Ejecuta `build.bat`
4. Corre `BitQuest.exe`

## Controles

| Tecla | Acción      |
|-------|-------------|
| W     | Arriba      |
| S     | Abajo       |
| A     | Izquierda   |
| D     | Derecha     |
| Q     | Salir       |

## Funciones en NASM

- `reproducirSonidoMoneda()` — beep al recoger moneda
- `reproducirSonidoPuerta()` — sonido al abrir puerta
- `reproducirSonidoVictoria()` — melodia al completar nivel

## Extras

- Colores ANSI en consola
- Pantalla de inicio y victoria
- Mapas cargados desde archivos .txt
- 4 niveles funcionales
- Bloques ASCII para visualizacion
