#ifndef JUGADOR_H
#define JUGADOR_H

#define FILAS 60
#define COLUMNAS 60
#define MARCO 20

typedef struct {
    int fila;
    int columna;
    int monedas;
    int Llave;
    int pasos;
} Jugador;

void CrearJugador(Jugador* j, int fila, int col);
void MoverJugador(Jugador* j, char direccion, char** mapa); //asi apunta a filas y columnas sin la necesidad de [60][60]
void RecogerObjeto(Jugador* j, char objeto);
int get_Fila(Jugador* j);
int get_Columnas(Jugador* j);

#endif