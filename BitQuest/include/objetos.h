// objetos.h
// Declara la funcion que maneja lo que le puede pasar al jugador
// cuando pisa una celda que no esta vacia: recoger monedas, agarrar la llave,
// y limpiar el objeto del mapa.
// Este archivo fue creado desde cero porque el original estaba vacio.

#ifndef OBJETOS_H
#define OBJETOS_H

#include "jugador.h"

// procesarObjeto: revisa que hay en la celda (fila, columna) del mapa
// y aplica el efecto correspondiente al jugador:
//   - Si es 'M' (moneda): suma 1 a las monedas del jugador y borra la moneda del mapa
//   - Si es 'K' (llave):  le da la llave al jugador y la borra del mapa
// Se llama justo antes de mover al jugador a la nueva celda.
void procesarObjeto(Jugador* j, char mapa[][COLUMNAS], int fila, int columna);

#endif // OBJETOS_H
