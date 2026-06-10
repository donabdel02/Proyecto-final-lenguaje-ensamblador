#ifndef JUEGO_H
#define JUEGO_H

// ============================================================
// juego.h - Constantes, estructuras y prototipos del juego
// BitQuest: Explorador de Matrices con C y NASM
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Dimensiones del mapa y ventana visible ---
#define FILAS_MAPA    60
#define COLS_MAPA     60
#define FILAS_VISTA   20
#define COLS_VISTA    20

// --- Caracteres del mapa ---
#define CHAR_PARED    '#'
#define CHAR_CAMINO   '.'
#define CHAR_JUGADOR  'P'
#define CHAR_MONEDA   'M'
#define CHAR_LLAVE    'K'
#define CHAR_PUERTA   'D'
#define CHAR_SALIDA   'E'

// --- Numero de niveles ---
#define NUM_NIVELES   3

// ============================================================
// Estructura que representa el estado del jugador
// ============================================================
typedef struct {
    int fila;           // Fila actual del jugador en el mapa completo
    int col;            // Columna actual del jugador en el mapa completo
    int tiene_llave;    // 1 si el jugador lleva la llave, 0 si no
    int monedas;        // Monedas recolectadas en el nivel actual
    int pasos;          // Pasos realizados en el nivel actual
    int monedas_total;  // Total acumulado de monedas en todos los niveles
    int pasos_total;    // Total acumulado de pasos en todos los niveles
} Jugador;

// ============================================================
// Prototipos de funciones en C (juego.c)
// ============================================================
void limpiar_pantalla(void);
void imprimir_vista(char mapa[FILAS_MAPA][COLS_MAPA], Jugador *j, int nivel, int total_monedas);
void mover_jugador(char mapa[FILAS_MAPA][COLS_MAPA], Jugador *j, char tecla);
void mostrar_resumen_nivel(int nivel, int monedas, int total_monedas, int pasos);
void mostrar_resumen_final(int monedas_total, int total_monedas_global, int pasos_total, int puntaje);
void iniciar_nivel(char mapa[FILAS_MAPA][COLS_MAPA], Jugador *j);
int  jugar_nivel(char mapa[FILAS_MAPA][COLS_MAPA], Jugador *j, int nivel);

// ============================================================
// Prototipos de funciones en NASM (rutinas.asm)
// Convencion de llamadas x64:
//   Linux/macOS : rdi, rsi, rdx, rcx, r8, r9
//   Windows     : rcx, rdx, r8, r9, pila
// ============================================================
extern long contar_caracter(char *mapa, long total_celdas, char caracter);
extern long validar_movimiento(char *mapa, long cols, long nueva_fila, long nueva_col);
extern long calcular_puntaje(long monedas, long pasos, long niveles);
extern long detectar_objeto(char *mapa, long cols, long fila, long col, char objeto);
extern long contar_celdas_libres(char *mapa, long total_celdas);

#endif // JUEGO_H
