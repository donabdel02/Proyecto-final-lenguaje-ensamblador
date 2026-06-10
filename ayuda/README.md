# BitQuest: Explorador de Matrices con C y NASM

Videojuego de laberinto en consola desarrollado con programación híbrida **C + NASM de 64 bits**.

---

## Requisitos

| Herramienta | Versión mínima | Descarga |
|-------------|---------------|----------|
| NASM        | 2.14+         | https://www.nasm.us/ |
| GCC 64-bit  | 7.0+          | https://www.mingw-w64.org/ (Windows) |
| Terminal    | Con soporte ANSI | Cualquier terminal moderna |

---

## Compilación y ejecución

### Windows

```bat
build.bat
BitQuest.exe
```

El script verifica que NASM y GCC estén en el PATH. Si no los encuentra, indica cómo instalarlos.

Pasos manuales equivalentes:
```bat
nasm -f win64 rutinas.asm -o rutinas.obj
gcc -Wall -O2 -o BitQuest.exe main.c juego.c rutinas.obj
BitQuest.exe
```

> **Nota sobre Windows:** El archivo `rutinas.asm` usa la convención de llamadas
> System V AMD64 (Linux). Para compilar correctamente en Windows con MinGW-w64,
> GCC traduce automáticamente los parámetros. Si se usa MSVC en lugar de GCC,
> será necesario adaptar las funciones NASM a la convención `__fastcall` de Windows
> (parámetros en `rcx`, `rdx`, `r8`, `r9`).

### Linux

```bash
chmod +x build.sh
./build.sh
./BitQuest
```

Pasos manuales equivalentes:
```bash
nasm -f elf64 rutinas.asm -o rutinas.o
gcc -Wall -O2 -o BitQuest main.c juego.c rutinas.o
./BitQuest
```

### macOS

```bash
chmod +x build.sh
./build.sh
./BitQuest
```

> En macOS los símbolos de NASM requieren prefijo `_`. Si hay errores de
> enlazado, agregar `_` al inicio de cada `global` en `rutinas.asm`
> (por ejemplo: `global _contar_caracter`).

---

## Estructura del proyecto

```
BitQuest/
├── main.c        → Punto de entrada, menú y control de niveles
├── juego.c       → Lógica del juego: mover jugador, imprimir vista, resúmenes
├── juego.h       → Constantes, estructuras y prototipos
├── mapas.h       → Los tres mapas de 60×60 en arreglos de caracteres
├── rutinas.asm   → Cinco funciones obligatorias en NASM de 64 bits
├── build.bat     → Script de compilación para Windows
├── build.sh      → Script de compilación para Linux/macOS
└── README.md     → Este archivo
```

---

## Controles del juego

| Tecla | Acción           |
|-------|-----------------|
| W / w | Mover arriba    |
| S / s | Mover abajo     |
| A / a | Mover izquierda |
| D / d | Mover derecha   |
| Q / q | Salir del juego |

---

## Elementos del mapa

| Símbolo | Color    | Significado                              |
|---------|----------|------------------------------------------|
| `P`     | Verde    | Jugador                                  |
| `#`     | Azul     | Pared (infranqueable)                    |
| `.`     | Blanco   | Camino libre                             |
| `M`     | Amarillo | Moneda (recolectable)                    |
| `K`     | Cian     | Llave (necesaria para abrir la puerta)   |
| `D`     | Rojo     | Puerta (solo se abre con la llave)       |
| `E`     | Magenta  | Salida (termina el nivel)                |

---

## Funciones en NASM

| Función               | Descripción                                      |
|-----------------------|--------------------------------------------------|
| `contar_caracter`     | Cuenta ocurrencias de un carácter en el mapa     |
| `validar_movimiento`  | Verifica que una celda no sea pared              |
| `calcular_puntaje`    | Calcula el puntaje: `monedas×100 - pasos×2 + niveles×500` |
| `detectar_objeto`     | Detecta si hay un objeto específico en una celda |
| `contar_celdas_libres`| Cuenta las celdas `.` del mapa                   |

---

## Fórmula de puntaje

```
puntaje = (monedas_recolectadas × 100) - (pasos_totales × 2) + (niveles_completados × 500)
```

Mínimo: 0 puntos (no puede ser negativo).
