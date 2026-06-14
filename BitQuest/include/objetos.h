#ifndef OBJETOS_H
#define OBJETOS_H

#include "jugador.h"

void procesarObjeto(Jugador* j, char mapa[][60], int fila, int columna);
void moverEnemigo(char mapa[][60], int* filaE, int* colE, int filaJ, int colJ);

#endif