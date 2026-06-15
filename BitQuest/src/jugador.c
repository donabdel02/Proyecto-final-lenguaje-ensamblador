#include "jugador.h"

void CrearJugador(Jugador* j, int fila, int columna) {
    j->fila = fila;
    j->columna = columna; //posicion inicial del jugador
    j->monedas = 0;
    j->Llave = 0;
    j->pasos = 0; //todo esto inicia las cosas en 0 para el jugador
}
