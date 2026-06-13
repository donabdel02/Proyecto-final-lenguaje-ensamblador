#ifndef JUEGO_H
#define JUEGO_H

#define FILAS        60
#define COLS         60
#define VIS          20
#define NUM_NIVELES   4

typedef struct {
    int fila;
    int col;
    int monedas;
    int tiene_llave;
    int pasos;
} Jugador;

typedef struct {
    char mapa[FILAS][COLS];
    int  total_monedas;
    int  total_libres;
    int  nivel_num;
} Nivel;

// Prototipos de juego.c
void imprimir_ventana(Nivel *n, Jugador *j);
void mover_jugador(Nivel *n, Jugador *j, char tecla);
void mostrar_hud(Jugador *j, int nivel_num);
void mostrar_resumen_nivel(Jugador *j, Nivel *n);
void mostrar_resumen_final(int monedas_total, int monedas_max,
                           int pasos, long puntaje);

// Prototipos de rutinas.asm
void reproducirSonidoMoneda();
void reproducirSonidoPuerta();
void reproducirSonidoVictoria();

#endif
