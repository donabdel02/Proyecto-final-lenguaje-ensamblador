#!/bin/bash
# ============================================================
# build.sh - Script de compilacion para BitQuest en Linux/macOS
# Requiere: NASM y GCC de 64 bits
# ============================================================

echo ""
echo " ============================================================"
echo "  BitQuest: Explorador de Matrices - Script de compilacion"
echo " ============================================================"
echo ""

# Detectar sistema operativo
OS="$(uname -s)"

# --- Verificar que NASM este disponible ---
if ! command -v nasm &> /dev/null; then
    echo " [ERROR] NASM no encontrado."
    if [ "$OS" = "Linux" ]; then
        echo " Instalalo con: sudo apt install nasm  (Debian/Ubuntu)"
        echo "             o: sudo dnf install nasm  (Fedora)"
    elif [ "$OS" = "Darwin" ]; then
        echo " Instalalo con: brew install nasm"
    fi
    exit 1
fi

# --- Verificar que GCC este disponible ---
if ! command -v gcc &> /dev/null; then
    echo " [ERROR] GCC no encontrado."
    if [ "$OS" = "Darwin" ]; then
        echo " Instala las herramientas de Xcode: xcode-select --install"
    fi
    exit 1
fi

echo " [1/3] Ensamblando rutinas.asm con NASM..."

if [ "$OS" = "Darwin" ]; then
    # macOS usa formato macho64 y prefijo _ en simbolos
    # Nota: en macOS los simbolos externos necesitan prefijo underscore
    # Se recomienda usar Linux para este proyecto.
    nasm -f macho64 rutinas.asm -o rutinas.o
else
    # Linux usa formato elf64
    nasm -f elf64 rutinas.asm -o rutinas.o
fi

if [ $? -ne 0 ]; then
    echo " [ERROR] Fallo el ensamblado de rutinas.asm"
    exit 1
fi
echo "       OK"

echo " [2/3] Compilando main.c y juego.c con GCC..."
gcc -Wall -Wextra -O2 -o BitQuest main.c juego.c rutinas.o -lm
if [ $? -ne 0 ]; then
    echo " [ERROR] Fallo la compilacion de C"
    exit 1
fi
echo "       OK"

echo " [3/3] Compilacion exitosa!"
echo ""
echo " ============================================================"
echo "  Ejecuta el juego con:  ./BitQuest"
echo " ============================================================"
echo ""
