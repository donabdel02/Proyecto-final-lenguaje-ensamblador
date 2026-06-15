# BitQuest - Explorador de Matrices

Videojuego de consola en C y NASM de 64 bits.

## Como compilar y ejecutar

1. Instala NASM.
2. Instala MinGW GCC.
3. Abre una terminal dentro de la carpeta `BitQuest`.
4. Ejecuta `build.bat`.
5. Corre `BitQuest.exe`.

## Controles

| Tecla | Accion |
|-------|--------|
| W     | Arriba |
| S     | Abajo |
| A     | Izquierda |
| D     | Derecha |
| Q     | Salir del juego |

## Funciones en NASM

- `contarCaracterMapa`: cuenta cuantas veces aparece un caracter dentro del mapa.
- `validarMovimiento`: valida si una celda destino no es pared.
- `calcularPuntaje`: calcula el puntaje final con monedas, pasos y niveles completados.
- `detectarObjeto`: revisa si en una posicion hay un objeto especifico.
- `contarCeldasLibres`: cuenta cuantas celdas libres quedan en el mapa.

## Extras

- Colores ANSI en consola.
- Pantalla de inicio y victoria.
- Mapas cargados desde archivos `.txt`.
- 4 niveles funcionales.
- Bloques ASCII para visualizacion.
- Musica por nivel con archivos `.wav`.
