// mapas.c
// Se encarga de leer los archivos .txt y cargar su contenido en la matriz del juego.
// Cada nivel tiene su propio archivo: lv1.txt, lv2.txt, lv3.txt, lv4.txt
// en la carpeta mapas/.

#include <stdio.h>
#include "../include/mapas.h"
#include "../include/jugador.h"

// cargar_mapa: abre el archivo .txt del nivel y llena la matriz mapa[60][60]
// con los caracteres que encuentra en cada linea.
// Parametros:
//   ruta  -> direccion del archivo, ej: "mapas/lv1.txt"
//   mapa  -> la matriz de 60x60 donde se guarda el nivel
// Regresa 1 si cargo bien, 0 si no pudo abrir el archivo.
//
// IMPORTANTE: se elimino el filtro que ignoraba lineas que empezaban con '#'
// porque en los mapas de laberinto '#' es el caracter de pared, no un comentario.
// Si se dejaba ese filtro, todas las filas de paredes se saltaban
// y el mapa quedaba con huecos donde no debia haberlos.
int cargar_mapa(const char *ruta, char mapa[][COLUMNAS]) {
    FILE *f = fopen(ruta, "r");
    if (!f) {
        printf("Error: no se pudo abrir %s\n", ruta);
        return 0;
    }

    char linea[COLUMNAS + 2]; // +2 para el salto de linea y el caracter nulo
    int fila = 0;

    while (fgets(linea, sizeof(linea), f) && fila < FILAS) {
        // Lee cada columna de la linea actual y la guarda en la matriz.
        // Si la linea termina antes de llegar a la columna 60,
        // rellena el resto con '.' (camino libre) para que no queden
        // caracteres basura en la memoria.
        for (int col = 0; col < COLUMNAS; col++) {
            if (linea[col] == '\n' || linea[col] == '\0')
                mapa[fila][col] = '.';
            else
                mapa[fila][col] = linea[col];
        }
        fila++;
    }

    fclose(f);
    return 1; // exito, el mapa quedo cargado
}