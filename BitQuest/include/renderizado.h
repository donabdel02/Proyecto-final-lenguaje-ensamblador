#ifndef RENDERIZADO_H
#define RENDERIZADO_H

#include "jugador.h"

void ImpresionMapa(char mapa[][COLUMNAS], Jugador* j); // ya recive los parametros para el mapa de 60x60 
void MostrarHUD(Jugador* j, int nivel); //todo lo que el usuario ocupa saber 
void mostrarPantallaInicio();
void mostrarPantallaVictoria(int monedas, int pasos);

#endif
