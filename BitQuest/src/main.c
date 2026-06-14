// BitQuest

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "colores.h"
#include "assets.h"
#include "jugador.h"
#include "mapas.h"
#include "renderizado.h"
#include "rutinas.h"
#include "objetos.h"

int main() {

    mostrarPantallaInicio();

    char mapa[FILAS][COLUMNAS];
    Jugador jugador;

    int totalMonedas  = 0;
    int pasosTotal    = 0;
    int nivelesOK     = 0;

    const char* archivos[] = {
        "mapas/lv1.txt",
        "mapas/lv2.txt",
        "mapas/lv3.txt",
        "mapas/lv4.txt"
    };

    const char* canciones[] = {
        "rolas/lv1.wav",
        "rolas/lv2.wav",
        "rolas/lv3.wav",
        "rolas/lv4.wav"
    };

    for (int nivel = 0; nivel < 4; nivel++) {

        if (!cargar_mapa(archivos[nivel], mapa)) {
            printf("No se pudo cargar %s\n", archivos[nivel]);
            continue;
        }

        int monedasNivel = contarCaracterMapa(
            &mapa[0][0], FILAS * COLUMNAS, CHAR_MONEDA);

        int filaInicio = 1, colInicio = 1;
        for (int i = 0; i < FILAS; i++)
            for (int j = 0; j < COLUMNAS; j++)
                if (mapa[i][j] == CHAR_JUGADOR) {
                    filaInicio = i;
                    colInicio  = j;
                }

        CrearJugador(&jugador, filaInicio, colInicio);

        int filaE = 3, colE = 3;
        mapa[filaE][colE] = 'X';

        PlaySound(canciones[nivel], NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

        int nivelTerminado = 0;
        char tecla;

        while (!nivelTerminado) {

            ImpresionMapa(mapa, &jugador);
            MostrarHUD(&jugador, nivel + 1);
            printf("Monedas en mapa: %d\n", monedasNivel);

            tecla = _getch();
            if (tecla == 'q' || tecla == 'Q') {
                nivelTerminado = 1;
                break;
            }

            int nf = jugador.fila;
            int nc = jugador.columna;
            if (tecla == 'w' || tecla == 'W') nf--;
            if (tecla == 's' || tecla == 'S') nf++;
            if (tecla == 'a' || tecla == 'A') nc--;
            if (tecla == 'd' || tecla == 'D') nc++;

            if (nf >= 0 && nf < FILAS && nc >= 0 && nc < COLUMNAS) {
                if (validarMovimiento(&mapa[0][0], COLUMNAS, nf, nc)) {

                    if (mapa[nf][nc] == CHAR_PUERTA) {
                        if (jugador.Llave)
                            mapa[nf][nc] = CHAR_LIBRE;
                        else
                            continue;
                    }

                    if (detectarObjeto(&mapa[0][0], COLUMNAS, nf, nc, CHAR_MONEDA) ||
                        detectarObjeto(&mapa[0][0], COLUMNAS, nf, nc, CHAR_LLAVE)) {
                        procesarObjeto(&jugador, mapa, nf, nc);
                    }

                    if (detectarObjeto(&mapa[0][0], COLUMNAS, nf, nc, CHAR_SALIDA)) {
                        nivelesOK++;
                        nivelTerminado = 1;
                    }

                    mapa[jugador.fila][jugador.columna] = CHAR_LIBRE;
                    jugador.fila    = nf;
                    jugador.columna = nc;
                    mapa[jugador.fila][jugador.columna] = CHAR_JUGADOR;
                    jugador.pasos++;
                }
            }

            moverEnemigo(mapa, &filaE, &colE, jugador.fila, jugador.columna);

            if (jugador.fila == filaE && jugador.columna == colE) {
                printf(COLOR_PARED "\n¡Te atrapo el enemigo!\n" COLOR_RESET);
                _getch();
                nivelTerminado = 1;
            }
        }

        PlaySound(NULL, NULL, 0);

        totalMonedas += jugador.monedas;
        pasosTotal   += jugador.pasos;

        int libres = contarCeldasLibres(&mapa[0][0], FILAS * COLUMNAS);
        printf(COLOR_TITULO "\n--- Nivel %d terminado ---\n" COLOR_RESET, nivel + 1);
        printf("Monedas recogidas: %d\n", jugador.monedas);
        printf("Pasos dados: %d\n", jugador.pasos);
        printf("Celdas libres en mapa: %d\n", libres);
        printf("\nPresiona cualquier tecla para continuar...\n");
        _getch();
    }

    int puntaje = calcularPuntaje(totalMonedas, pasosTotal, nivelesOK);
    mostrarPantallaVictoria(totalMonedas, pasosTotal);
    printf(COLOR_TITULO "Puntaje final: %d\n" COLOR_RESET, puntaje);
    printf("Presiona cualquier tecla para salir...\n");
    _getch();

    return 0;
}