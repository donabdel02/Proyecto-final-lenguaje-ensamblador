// juego.c
// Implementacion de funciones del juego

#include <stdio.h>
#include "../include/juego.h"
#include "../include/colores.h"
#include "../include/assets.h"

void imprimir_ventana(Nivel *n, Jugador *j) {
    // TODO: implementar ventana 20x20
}

void mover_jugador(Nivel *n, Jugador *j, char tecla) {
    // TODO: implementar movimiento con WASD
}

void mostrar_hud(Jugador *j, int nivel_num) {
    // TODO: mostrar nivel, monedas, llaves
}

void mostrar_resumen_nivel(Jugador *j, Nivel *n) {
    // TODO: mostrar resumen al terminar nivel
}

void mostrar_resumen_final(int monedas_total, int monedas_max,
                           int pasos, long puntaje) {
    // TODO: mostrar resumen final del juego
}
