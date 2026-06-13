#ifndef RENDERIZADO_H
#define RENDERIZADO_H

#include "jugador.h"

void ImpresionMapa(char** mapa, Jugador* j);
void MostrarHUD(Jugador* j, int nivel); //todo lo que el usuario ocupa saber 
void mostrarPantallaInicio();
void mostrarPantallaVictoria(int monedas, int pasos);

#endif