// main.c
// Punto de entrada del juego BitQuest.
// Este archivo fue reescrito porque el original solo tenia funciones vacias
// y no conectaba ninguno de los modulos del proyecto.
//
// Ahora hace lo siguiente en orden:
//   1. Muestra la pantalla de inicio
//   2. Recorre los 4 niveles en orden
//   3. En cada nivel: carga el mapa, busca al jugador, reproduce musica,
//      lee teclas WASD, valida movimiento con NASM, recoge objetos,
//      y detecta si llego a la salida
//   4. Al terminar todos los niveles: calcula puntaje final con NASM
//      y muestra la pantalla de victoria

#include <stdio.h>
#include <conio.h>      // _getch(): lee una tecla sin necesitar Enter (solo Windows)
#include <windows.h>    // PlaySound(): para reproducir musica WAV por nivel
#include "colores.h"    // codigos ANSI para colores en consola
#include "assets.h"     // caracteres del mapa: CHAR_PARED, CHAR_MONEDA, etc.
#include "jugador.h"    // struct Jugador y funcion CrearJugador
#include "mapas.h"      // cargar_mapa: lee el archivo .txt y llena la matriz
#include "renderizado.h"// ImpresionMapa, MostrarHUD, pantallas de inicio y victoria
#include "rutinas.h"    // prototipos de las 5 rutinas NASM obligatorias
#include "objetos.h"    // procesarObjeto

int main() {

    // --- Pantalla de inicio (punto extra) ---
    // Definida en renderizado.c, muestra titulo y controles
    mostrarPantallaInicio();

    // Variables del mapa y jugador
    char mapa[FILAS][COLUMNAS]; // matriz 60x60 que representa el nivel actual
    Jugador jugador;            // struct con posicion, monedas, llave y pasos

    // Acumuladores para el resumen final
    int totalMonedas = 0; // monedas sumadas de todos los niveles
    int pasosTotal   = 0; // pasos sumados de todos los niveles
    int nivelesOK    = 0; // cuantos niveles se completaron llegando a la salida
    int salirJuego   = 0; // indica si el jugador quiere cerrar todo el juego

    // Rutas de los archivos de mapa, uno por nivel
    // El punto extra de "mas de 3 niveles" se cumple con estos 4 archivos
    const char* archivos[] = {
        "mapas/lv1.txt",
        "mapas/lv2.txt",
        "mapas/lv3.txt",
        "mapas/lv4.txt"
    };

    // Rutas de las canciones, una distinta por nivel (punto extra de musica)
    // La musica NO suena en pantalla de inicio ni en pantalla de victoria,
    // solo durante el juego de cada nivel
    const char* canciones[] = {
        "rolas/lv1.wav",
        "rolas/lv2.wav",
        "rolas/lv3.wav",
        "rolas/lv4.wav"
    };

    // --- Bucle principal: recorre los 4 niveles en orden ---
    for (int nivel = 0; nivel < 4 && !salirJuego; nivel++) {

        // Cargar el archivo .txt del nivel actual en la matriz mapa[][]
        // Si el archivo no existe o no se puede abrir, salta al siguiente nivel
        if (!cargar_mapa(archivos[nivel], mapa)) {
            printf("No se pudo cargar %s\n", archivos[nivel]);
            continue;
        }

        // Contar cuantas monedas hay en el mapa usando la rutina NASM obligatoria 1
        // Sirve para mostrarle al jugador cuantas monedas puede recoger en total
        int monedasNivel = contarCaracterMapa(
            &mapa[0][0], FILAS * COLUMNAS, CHAR_MONEDA);

        // Buscar la posicion inicial del jugador 'P' en el mapa cargado
        // El jugador empieza donde el archivo .txt tenga una 'P'
        int filaInicio = 1, colInicio = 1; // valores por defecto si no encuentra 'P'
        for (int i = 0; i < FILAS; i++)
            for (int j = 0; j < COLUMNAS; j++)
                if (mapa[i][j] == CHAR_JUGADOR) {
                    filaInicio = i;
                    colInicio  = j;
                }

        // Inicializar al jugador en su posicion de inicio con todo en cero
        CrearJugador(&jugador, filaInicio, colInicio);

        // Reproducir la cancion del nivel actual en segundo plano (SND_ASYNC)
        // SND_LOOP hace que se repita hasta que se detenga explicitamente
        PlaySound(canciones[nivel], NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

        int nivelTerminado = 0; // bandera: 1 cuando el nivel debe terminar
        char tecla;             // guarda la tecla que presiono el jugador

        // --- Bucle del nivel: se repite hasta que el jugador llegue a la salida
        //     o presione Q para salir ---
        while (!nivelTerminado) {

            // Dibujar el mapa con ventana 20x20 centrada en el jugador (renderizado.c)
            ImpresionMapa(mapa, &jugador);

            // Mostrar HUD: nivel actual, monedas, pasos y si tiene llave
            MostrarHUD(&jugador, nivel + 1);
            printf("Monedas en mapa: %d\n", monedasNivel);

            // Leer la tecla sin esperar Enter
            tecla = _getch();

            // Q o q: salir del juego completo
            if (tecla == 'q' || tecla == 'Q') {
                salirJuego = 1;
                nivelTerminado = 1;
                break;
            }

            // Calcular la nueva posicion segun la tecla presionada
            // WASD en mayusculas y minusculas para que funcione de las dos formas
            int nf = jugador.fila;
            int nc = jugador.columna;
            int teclaMovimiento = 1; // ayuda a ignorar teclas que no sean WASD
            if (tecla == 'w' || tecla == 'W') nf--;
            else if (tecla == 's' || tecla == 'S') nf++;
            else if (tecla == 'a' || tecla == 'A') nc--;
            else if (tecla == 'd' || tecla == 'D') nc++;
            else teclaMovimiento = 0;

            // Si no fue una tecla valida, no mueve ni suma pasos
            if (!teclaMovimiento) continue;

            // Verificar que la nueva posicion este dentro del mapa
            if (nf >= 0 && nf < FILAS && nc >= 0 && nc < COLUMNAS) {

                // Validar con rutina NASM obligatoria 2 que la celda no sea pared
                // validarMovimiento regresa 1 si es valido, 0 si es pared
                if (validarMovimiento(&mapa[0][0], COLUMNAS, nf, nc)) {

                    // Si hay una puerta, solo puede pasar si tiene la llave
                    // Si no tiene llave, el movimiento se cancela (continue)
                    if (mapa[nf][nc] == CHAR_PUERTA) {
                        if (jugador.Llave)
                            mapa[nf][nc] = CHAR_LIBRE; // abre la puerta
                        else
                            continue; // bloqueado: no tiene llave
                    }

                    // Detectar si hay moneda o llave en la nueva celda (NASM obligatoria 4)
                    // y aplicar el efecto correspondiente al jugador
                    if (detectarObjeto(&mapa[0][0], COLUMNAS, nf, nc, CHAR_MONEDA) ||
                        detectarObjeto(&mapa[0][0], COLUMNAS, nf, nc, CHAR_LLAVE)) {
                        procesarObjeto(&jugador, mapa, nf, nc);
                    }

                    // Detectar si el jugador llego a la salida 'E' (NASM obligatoria 4)
                    // Si llego, el nivel cuenta como completado
                    if (detectarObjeto(&mapa[0][0], COLUMNAS, nf, nc, CHAR_SALIDA)) {
                        nivelesOK++;
                        nivelTerminado = 1;
                    }

                    // Mover al jugador en el mapa:
                    // primero borra su posicion anterior con '.'
                    // luego pone 'P' en la nueva posicion
                    mapa[jugador.fila][jugador.columna] = CHAR_LIBRE;
                    jugador.fila    = nf;
                    jugador.columna = nc;
                    mapa[jugador.fila][jugador.columna] = CHAR_JUGADOR;
                    jugador.pasos++; // contar cada paso para el puntaje final
                }
            }

        }

        // Detener la musica al terminar el nivel
        // NULL como primer argumento detiene cualquier sonido activo
        PlaySound(NULL, NULL, 0);

        // Si se presiono Q, termina el programa sin pasar al siguiente nivel
        if (salirJuego) return 0;

        // Acumular estadisticas del nivel para el resumen final
        totalMonedas += jugador.monedas;
        pasosTotal   += jugador.pasos;

        // Contar celdas libres del nivel con rutina NASM obligatoria 5
        int libres = contarCeldasLibres(&mapa[0][0], FILAS * COLUMNAS);

        // Mostrar resumen del nivel antes de pasar al siguiente
        printf(COLOR_TITULO "\n--- Nivel %d terminado ---\n" COLOR_RESET, nivel + 1);
        printf("Monedas recogidas este nivel: %d\n", jugador.monedas);
        printf("Pasos dados este nivel: %d\n", jugador.pasos);
        printf("Celdas libres en el mapa: %d\n", libres);
        printf("\nPresiona cualquier tecla para continuar...\n");
        _getch();
    }

    // --- Fin del juego ---

    // Calcular puntaje final con rutina NASM obligatoria 3
    // Formula: (monedas x 250) + (niveles completados x 1000) - (pasos x 5)
    int puntaje = calcularPuntaje(totalMonedas, pasosTotal, nivelesOK);

    // Mostrar pantalla de victoria con todas las estadisticas finales.
    mostrarPantallaVictoria(totalMonedas, pasosTotal, puntaje);

    return 0;
}
