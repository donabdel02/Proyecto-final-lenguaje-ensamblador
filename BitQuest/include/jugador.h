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

#endif
