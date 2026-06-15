// objetos.c
// Implementa la logica de los objetos del juego.
// Este archivo fue creado desde cero porque el original estaba vacio.
// Trabaja junto con objetos.h y se conecta con main.c para que el
// jugador pueda interactuar con el mapa.

#include "objetos.h"
#include "assets.h"

// procesarObjeto: se ejecuta cuando el jugador va a pisar una celda con objeto.
// Revisa el caracter de esa celda y aplica el efecto:
//   CHAR_MONEDA ('M') -> aumenta el contador de monedas y limpia la celda
//   CHAR_LLAVE  ('K') -> activa la llave del jugador y limpia la celda
// Limpiar la celda significa poner '.' para que el objeto no aparezca
// dos veces en el mapa al volver a renderizar.
void procesarObjeto(Jugador* j, char mapa[][COLUMNAS], int fila, int columna) {
    char celda = mapa[fila][columna];

    if (celda == CHAR_MONEDA) {
        j->monedas++;                    // suma 1 moneda al jugador
        mapa[fila][columna] = CHAR_LIBRE; // borra la moneda del mapa
    }
    if (celda == CHAR_LLAVE) {
        j->Llave = 1;                    // el jugador ahora tiene llave
        mapa[fila][columna] = CHAR_LIBRE; // borra la llave del mapa
    }
}
