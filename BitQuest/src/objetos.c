#include "objetos.h"
#include "assets.h"

void procesarObjeto(Jugador* j, char mapa[][60], int fila, int columna) {
    char celda = mapa[fila][columna];

    if (celda == CHAR_MONEDA) {
        j->monedas++;
        mapa[fila][columna] = CHAR_LIBRE;
    }
    if (celda == CHAR_LLAVE) {
        j->Llave = 1;
        mapa[fila][columna] = CHAR_LIBRE;
    }
}

void moverEnemigo(char mapa[][60], int* filaE, int* colE, int filaJ, int colJ) {
    int nuevaFila = *filaE;
    int nuevaCol  = *colE;

    if (filaJ > *filaE) nuevaFila++;
    else if (filaJ < *filaE) nuevaFila--;

    if (colJ > *colE) nuevaCol++;
    else if (colJ < *colE) nuevaCol--;

    if (mapa[nuevaFila][nuevaCol] == CHAR_LIBRE) {
        mapa[*filaE][*colE] = CHAR_LIBRE;
        *filaE = nuevaFila;
        *colE  = nuevaCol;
        mapa[*filaE][*colE] = 'X';
    }
}