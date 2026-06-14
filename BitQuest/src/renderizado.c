#include <stdio.h>
#include <stdlib.h>
#include "renderizado.h"
#include "colores.h"
#include "assets.h"
#include "jugador.h"

void ImpresionMapa(char mapa[][COLUMNAS], Jugador* j) { //aqui tambien ya tiene los parametros correctos para el para de 60x60 
    int VistaFila = j->fila - MARCO/2;
    int VistaColumna = j->columna - MARCO/2;
    
    if (VistaFila < 0) VistaFila = 0;
    if (VistaColumna < 0) VistaColumna = 0;
    if (VistaFila > FILAS - MARCO) VistaFila = FILAS - MARCO;
    if (VistaColumna > COLUMNAS - MARCO) VistaColumna = COLUMNAS - MARCO;
    
    system("cls");
    
    for (int i = VistaFila; i < VistaFila + MARCO; i++) {
        for (int j = VistaColumna; j < VistaColumna + MARCO; j++) {
            char celda = mapa[i][j]; // agarra el caracter de la celda actual para decidir como imprimirlo
            
            if (celda == CHAR_PARED) {
                printf(COLOR_PARED "%s" COLOR_RESET, VISUAL_PARED); // si es pared la imprime con el visual de pared
            } else if (celda == CHAR_JUGADOR) {
                printf(COLOR_JUGADOR "%s" COLOR_RESET, VISUAL_JUGADOR); // si es jugador la imprime con el visual de jugador
            } else if (celda == CHAR_MONEDA) {
                printf(COLOR_MONEDA "%s" COLOR_RESET, VISUAL_MONEDA); // si es moneda la imprime con el visual de moneda
            } else if (celda == CHAR_LLAVE) {
                printf(COLOR_LLAVE "%s" COLOR_RESET, VISUAL_LLAVE); // si es llave la imprime con el visual de llave
            } else if (celda == CHAR_PUERTA) {
                printf(COLOR_PUERTA "%s" COLOR_RESET, VISUAL_PUERTA); // si es puerta la imprime con el visual de puerta
            } else if (celda == CHAR_SALIDA) {
                printf(COLOR_SALIDA "%s" COLOR_RESET, VISUAL_SALIDA); // si es salida la imprime con el visual de salida
            } else if (celda == CHAR_LIBRE) {
                printf(VISUAL_LIBRE); // camino libre, se imprime como espacio para que parezca pasillo
            } else {
                printf("%c ", celda); // cualquier otro caracter conserva el ancho de dos columnas
            }
        }
        printf("\n");
    }
}

void MostrarHUD(Jugador* j, int nivel) {
    printf(COLOR_JUGADOR "Nivel: %d | Monedas: %d | Pasos: %d | Llave: %s" COLOR_RESET "\n", // esta funcion muestra el HUD con la informacion del jugador, como el nivel actual, las monedas recogidas, los pasos dados y si tiene la llave o no
        nivel, j->monedas, j->pasos, j->Llave ? "SI" : "NO"); 
}

void mostrarPantallaInicio() {
    system("cls");
    printf(COLOR_TITULO "\n");
    printf("BITQUEST\n");
    printf("Explorador de Matrices\n");
    printf(COLOR_RESET "\n\n");
    printf("Controles:\n");
    printf(" W - Arriba\n");
    printf(" S - Abajo\n");
    printf(" A - Izquierda\n");
    printf(" D - Derecha\n");
    printf(" Q - Salir\n\n");
    printf("Presione ENTER para comenzar\n");
    getchar();
}

void mostrarPantallaVictoria(int monedas, int pasos) {
    system("cls");
    printf(COLOR_TITULO "\n");
    printf("Grande vro pudiste salir del laberinto\n");
    printf(COLOR_RESET "\n");
    printf("Monedas recogidas: %d\n", monedas);
    printf("Pasos dados: %d\n", pasos);
    printf("\nPresione ENTER para salir\n");
    getchar();
}
