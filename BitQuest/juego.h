// para definir matrices, structs y funciones del juego 

#ifndef JUEGO_H
#define JUEGO_H

#define filas 60
#define cols 60
#define vis 20
#define num_niveles 4

typedef struct {
    int fila;
    int col;
    int monedas;
    int tiene_llave;
    int pasos;
} Jugador;

typedef struct {
    char mapa[filas][cols];
    int total_monedas;
    int total_libres;
    int nivel_num;
} Nivel;

// prototipos (implementar en juego.c)
void imprimir_ventana(Nivel* n, Jugador* j);
void mover_jugador(Nivel* n, Jugador* j, char tecla);
void mostrar_hud(Jugador* j, int nivel_num);
void mostrar_resumen_nivel(Jugador* j, Nivel* n);
void mostrar_resumen_final(int monedas_total, int monedas_max, int pasos, long puntaje);

#endif