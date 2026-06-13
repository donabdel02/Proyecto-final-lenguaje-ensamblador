#include "jugador.h"
#include "assets.h"

void CrearJugador(Jugador* j, int fila, int columna) {
    j->fila = fila;
    j->columna = columna; //posicion inicial del jugador
    j->monedas = 0;
    j->Llave = 0;
    j->pasos = 0; //todo esto inicia las cosas en 0 para el jugador
}

void MoverJugador(Jugador* j, char direccion, char** mapa) {
    int nueva_fila = j->fila;
    int nueva_columna = j->columna;  //guarda la posicuion del jugador y si puede avanzar la va actualizando, si no se queda igual

    if (direccion == 'w') nueva_fila--;
    if (direccion == 's') nueva_fila++;
    if (direccion == 'a') nueva_columna--;
    if (direccion == 'd') nueva_columna++; //controles de toda la laif
    
    if (nueva_fila >= 0 && nueva_fila < FILAS && 
        nueva_columna >= 0 && nueva_columna < COLUMNAS && //verifica que no se salga del mapa
        mapa[nueva_fila][nueva_columna] != CHAR_PARED &&
        !(mapa[nueva_fila][nueva_columna] == CHAR_PUERTA && !j->Llave)) { //valida que no pase puerta sin llave
        
        mapa[j->fila][j->columna] = CHAR_LIBRE; // aqui reemplaza la posicion del jugador por un espacio en blanco para que no se quede la marca del jugador en el mapa
        j->fila = nueva_fila;
        j->columna = nueva_columna; // estas 2 calculan de que la nueva posion del jugador 
        mapa[j->fila][j->columna] = CHAR_JUGADOR; // aqui tal cual pone al jugador en su nueva posicion
        j->pasos++; // sirve nomas pa saber cuanto avanzo el jugador
    }
}

void RecogerObjeto(Jugador* j, char objeto) {
    if (objeto == CHAR_MONEDA) j->monedas++; // es para tener un conteo de las monedas del jugador (M)
    if (objeto == CHAR_LLAVE) j->Llave = 1; // indica si el jugador ya tiene la llave (K)
}

int get_Fila(Jugador* j) {
    return j->fila;
}

int get_Columnas(Jugador* j) {
    return j->columna;
}

//estas nomas son para saber la posicion del jugador en el mapa