// objetos.c
// Implementa la logica de los objetos del juego y el movimiento del enemigo.
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
void procesarObjeto(Jugador* j, char mapa[][60], int fila, int columna) {
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

// moverEnemigo: calcula hacia donde debe moverse el enemigo para acercarse
// al jugador y actualiza su posicion en el mapa.
// El enemigo se mueve un solo paso por turno.
// Logica de movimiento:
//   - Si el jugador esta mas abajo  -> el enemigo baja una fila
//   - Si el jugador esta mas arriba -> el enemigo sube una fila
//   - Si el jugador esta mas a la derecha -> el enemigo va a la derecha
//   - Si el jugador esta mas a la izquierda -> el enemigo va a la izquierda
// El enemigo NO puede atravesar paredes: solo se mueve si la celda destino
// es CHAR_LIBRE ('.').
// En el mapa el enemigo se representa con 'X'.
void moverEnemigo(char mapa[][60], int* filaE, int* colE, int filaJ, int colJ) {
    int nuevaFila = *filaE;
    int nuevaCol  = *colE;

    // Calcular direccion vertical
    if (filaJ > *filaE) nuevaFila++;       // jugador abajo: enemigo baja
    else if (filaJ < *filaE) nuevaFila--;  // jugador arriba: enemigo sube

    // Calcular direccion horizontal
    if (colJ > *colE) nuevaCol++;          // jugador a la derecha
    else if (colJ < *colE) nuevaCol--;     // jugador a la izquierda

    // Solo mover si la celda destino esta libre, para no atravesar paredes
    if (mapa[nuevaFila][nuevaCol] == CHAR_LIBRE) {
        mapa[*filaE][*colE] = CHAR_LIBRE;  // borra al enemigo de su posicion anterior
        *filaE = nuevaFila;
        *colE  = nuevaCol;
        mapa[*filaE][*colE] = 'X';         // dibuja al enemigo en su nueva posicion
    }
}