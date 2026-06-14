// mapas.c
// Carga mapas desde archivos .txt

#include <stdio.h>
#include "../include/mapas.h"
#include "../include/jugador.h"

int cargar_mapa(const char *ruta, char mapa[][COLUMNAS]) {
    FILE *f = fopen(ruta, "r");
    if (!f) {
        printf("Error: no se pudo abrir %s\n", ruta);
        return 0;
    }

    char linea[COLUMNAS + 2];
    int fila = 0;

    while (fgets(linea, sizeof(linea), f) && fila < FILAS) {
        // Ignorar lineas de comentario
        if (linea[0] == '#') continue;

        for (int col = 0; col < COLUMNAS; col++) {
            if (linea[col] == '\n' || linea[col] == '\0')
                mapa[fila][col] = '.';
            else
                mapa[fila][col] = linea[col];
        }
        fila++;
    }

    fclose(f);
    return 1; // exito
}
