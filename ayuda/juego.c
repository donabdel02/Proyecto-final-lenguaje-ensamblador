// ============================================================
// juego.c - Logica principal del juego BitQuest
// BitQuest: Explorador de Matrices con C y NASM
// ============================================================

#include "juego.h"
#ifndef _WIN32
#include <termios.h>
#include <unistd.h>
#endif

// ============================================================
// limpiar_pantalla
// Limpia la terminal usando una secuencia ANSI portabl.
// En Windows sin soporte ANSI se puede usar system("cls").
// ============================================================
void limpiar_pantalla(void) {
#ifdef _WIN32
    system("cls");
#else
    // Secuencia ANSI: mover cursor a inicio y borrar pantalla
    printf("\033[H\033[2J");
    fflush(stdout);
#endif
}

// ============================================================
// imprimir_vista
// Muestra la ventana visible de 20x20 centrada (o ajustada)
// alrededor del jugador dentro del mapa de 60x60.
// Tambien muestra el HUD con informacion del estado actual.
// ============================================================
void imprimir_vista(char mapa[FILAS_MAPA][COLS_MAPA], Jugador *j, int nivel, int total_monedas) {
    // Calcular la esquina superior-izquierda de la ventana visible.
    // Intentamos centrar la vista en el jugador.
    int inicio_fila = j->fila - FILAS_VISTA / 2;
    int inicio_col  = j->col  - COLS_VISTA  / 2;

    // Ajustar para no salir de los limites del mapa
    if (inicio_fila < 0) inicio_fila = 0;
    if (inicio_col  < 0) inicio_col  = 0;
    if (inicio_fila + FILAS_VISTA > FILAS_MAPA) inicio_fila = FILAS_MAPA - FILAS_VISTA;
    if (inicio_col  + COLS_VISTA  > COLS_MAPA)  inicio_col  = COLS_MAPA  - COLS_VISTA;

    limpiar_pantalla();

    // --- HUD superior ---
    printf("============================================================\n");
    printf("  BitQuest: Explorador de Matrices          Nivel: %d / %d\n", nivel, NUM_NIVELES);
    printf("============================================================\n");
    printf("  Llave: %-3s  |  Monedas: %2d / %2d  |  Pasos: %d\n",
           j->tiene_llave ? "SI" : "No",
           j->monedas,
           total_monedas,
           j->pasos);
    printf("------------------------------------------------------------\n");

    // --- Ventana visible (20 x 20) ---
    for (int vf = 0; vf < FILAS_VISTA; vf++) {
        int fila_real = inicio_fila + vf;
        printf("  ");
        for (int vc = 0; vc < COLS_VISTA; vc++) {
            int col_real = inicio_col + vc;
            char celda = mapa[fila_real][col_real];

            // Colorear segun el caracter (ANSI escape codes)
            switch (celda) {
                case CHAR_JUGADOR:
                    printf("\033[1;32mP\033[0m");  // Verde brillante
                    break;
                case CHAR_PARED:
                    printf("\033[1;34m#\033[0m");  // Azul
                    break;
                case CHAR_MONEDA:
                    printf("\033[1;33mM\033[0m");  // Amarillo
                    break;
                case CHAR_LLAVE:
                    printf("\033[1;36mK\033[0m");  // Cian
                    break;
                case CHAR_PUERTA:
                    printf("\033[1;31mD\033[0m");  // Rojo
                    break;
                case CHAR_SALIDA:
                    printf("\033[1;35mE\033[0m");  // Magenta
                    break;
                default:
                    printf("%c", celda);
                    break;
            }
        }
        printf("\n");
    }

    printf("------------------------------------------------------------\n");
    printf("  Controles: W=Arriba  A=Izq  S=Abajo  D=Der  Q=Salir\n");
    printf("============================================================\n");
    fflush(stdout);
}

// ============================================================
// mover_jugador
// Procesa la tecla presionada y actualiza la posicion del
// jugador si el movimiento es valido (usando NASM).
// Tambien gestiona la recoleccion de objetos.
// ============================================================
void mover_jugador(char mapa[FILAS_MAPA][COLS_MAPA], Jugador *j, char tecla) {
    int nueva_fila = j->fila;
    int nueva_col  = j->col;

    // Calcular la nueva posicion segun la tecla
    switch (tecla) {
        case 'W': case 'w': nueva_fila--; break;
        case 'S': case 's': nueva_fila++; break;
        case 'A': case 'a': nueva_col--;  break;
        case 'D': case 'd': nueva_col++;  break;
        default: return;  // Tecla no reconocida
    }

    // Verificar limites del mapa
    if (nueva_fila < 0 || nueva_fila >= FILAS_MAPA) return;
    if (nueva_col  < 0 || nueva_col  >= COLS_MAPA)  return;

    // --- Llamada a NASM: validar_movimiento ---
    // Verifica que la celda destino no sea una pared
    long puede_mover = validar_movimiento(
        (char *)mapa,
        (long)COLS_MAPA,
        (long)nueva_fila,
        (long)nueva_col
    );

    if (!puede_mover) return;  // Bloqueado por pared

    // --- Verificar si hay una puerta en la posicion destino ---
    long hay_puerta = detectar_objeto(
        (char *)mapa,
        (long)COLS_MAPA,
        (long)nueva_fila,
        (long)nueva_col,
        CHAR_PUERTA
    );

    if (hay_puerta) {
        if (!j->tiene_llave) {
            // No tiene llave: no puede pasar
            printf("\n  [!] Necesitas la llave para abrir esta puerta!\n");
            fflush(stdout);
            return;
        }
        // Tiene llave: abrir la puerta (convertir en camino libre)
        mapa[nueva_fila][nueva_col] = CHAR_CAMINO;
        j->tiene_llave = 0;  // Usar la llave
    }

    // --- Verificar si hay una moneda en la posicion destino ---
    long hay_moneda = detectar_objeto(
        (char *)mapa,
        (long)COLS_MAPA,
        (long)nueva_fila,
        (long)nueva_col,
        CHAR_MONEDA
    );

    if (hay_moneda) {
        j->monedas++;
        mapa[nueva_fila][nueva_col] = CHAR_CAMINO;  // Quitar la moneda del mapa
    }

    // --- Verificar si hay una llave en la posicion destino ---
    long hay_llave = detectar_objeto(
        (char *)mapa,
        (long)COLS_MAPA,
        (long)nueva_fila,
        (long)nueva_col,
        CHAR_LLAVE
    );

    if (hay_llave) {
        j->tiene_llave = 1;
        mapa[nueva_fila][nueva_col] = CHAR_CAMINO;
    }

    // Mover al jugador: limpiar posicion anterior y colocar en nueva
    mapa[j->fila][j->col]       = CHAR_CAMINO;
    mapa[nueva_fila][nueva_col] = CHAR_JUGADOR;

    j->fila = nueva_fila;
    j->col  = nueva_col;
    j->pasos++;
}

// ============================================================
// mostrar_resumen_nivel
// Muestra el resumen al terminar un nivel.
// ============================================================
void mostrar_resumen_nivel(int nivel, int monedas, int total_monedas, int pasos) {
    printf("\n");
    printf("=================================\n");
    printf("  Nivel %d completado!\n", nivel);
    printf("  Monedas recolectadas: %d / %d\n", monedas, total_monedas);
    printf("  Pasos realizados: %d\n", pasos);
    printf("=================================\n");
    printf("\n  Presiona cualquier tecla para continuar...\n");
    fflush(stdout);
    getchar();
}

// ============================================================
// mostrar_resumen_final
// Muestra el resumen final al completar los 3 niveles.
// ============================================================
void mostrar_resumen_final(int monedas_total, int total_monedas_global, int pasos_total, int puntaje) {
    limpiar_pantalla();
    printf("\n");
    printf("  ************************************\n");
    printf("  *                                  *\n");
    printf("  *     FELICIDADES, GANASTE!        *\n");
    printf("  *     BitQuest completado          *\n");
    printf("  *                                  *\n");
    printf("  ************************************\n");
    printf("\n");
    printf("=================================\n");
    printf("  Juego completado!\n");
    printf("  Monedas totales recolectadas: %d / %d\n", monedas_total, total_monedas_global);
    printf("  Pasos totales: %d\n", pasos_total);
    printf("  Niveles completados: %d\n", NUM_NIVELES);
    printf("  Puntaje final: %d\n", puntaje);
    printf("=================================\n\n");
    fflush(stdout);
}

// ============================================================
// iniciar_nivel
// Busca la posicion inicial 'P' en el mapa y configura
// el estado inicial del jugador para ese nivel.
// ============================================================
void iniciar_nivel(char mapa[FILAS_MAPA][COLS_MAPA], Jugador *j) {
    j->tiene_llave = 0;
    j->monedas     = 0;
    j->pasos       = 0;

    // Buscar la posicion inicial del jugador en el mapa
    for (int r = 0; r < FILAS_MAPA; r++) {
        for (int c = 0; c < COLS_MAPA; c++) {
            if (mapa[r][c] == CHAR_JUGADOR) {
                j->fila = r;
                j->col  = c;
                return;
            }
        }
    }
    // Si no se encontro 'P', colocar en (1,1) por defecto
    j->fila = 1;
    j->col  = 1;
    mapa[1][1] = CHAR_JUGADOR;
}

// ============================================================
// jugar_nivel
// Bucle principal de un nivel. Lee teclas y actualiza el
// estado hasta que el jugador llega a la salida o presiona Q.
// Retorna 1 si completo el nivel, 0 si eligio salir.
// ============================================================
int jugar_nivel(char mapa[FILAS_MAPA][COLS_MAPA], Jugador *j, int nivel) {
    // --- Calcular total de monedas con NASM ---
    long total_monedas = contar_caracter(
        (char *)mapa,
        (long)(FILAS_MAPA * COLS_MAPA),
        CHAR_MONEDA
    );

    // --- Calcular celdas libres con NASM (mostrar al inicio) ---
    long celdas_libres = contar_celdas_libres(
        (char *)mapa,
        (long)(FILAS_MAPA * COLS_MAPA)
    );

    limpiar_pantalla();
    printf("\n");
    printf("  ====================================\n");
    printf("  Iniciando Nivel %d\n", nivel);
    printf("  Monedas disponibles : %ld\n", total_monedas);
    printf("  Celdas libres en el mapa: %ld\n", celdas_libres);
    printf("  ====================================\n");
    printf("  Presiona cualquier tecla para empezar...\n");
    fflush(stdout);
    getchar();

    // Configurar terminal para lectura sin eco (Linux/macOS)
#ifndef _WIN32
    struct termios t_old, t_new;
    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    t_new.c_cc[VMIN]  = 1;
    t_new.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);
#endif

    int nivel_completado = 0;

    while (1) {
        imprimir_vista(mapa, j, nivel, (int)total_monedas);

        // Leer tecla
        int tecla = getchar();
        if (tecla == EOF) break;

        char c = (char)tecla;

        // Salir del juego
        if (c == 'Q' || c == 'q') {
            nivel_completado = 0;
            break;
        }

        // Mover jugador
        mover_jugador(mapa, j, c);

        // Verificar si el jugador llego a la salida
        long en_salida = detectar_objeto(
            (char *)mapa,
            (long)COLS_MAPA,
            (long)j->fila,
            (long)j->col,
            CHAR_SALIDA
        );

        if (en_salida) {
            nivel_completado = 1;
            break;
        }
    }

    // Restaurar terminal
#ifndef _WIN32
    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
#endif

    if (nivel_completado) {
        j->monedas_total += j->monedas;
        j->pasos_total   += j->pasos;
        mostrar_resumen_nivel(nivel, j->monedas, (int)total_monedas, j->pasos);
    }

    return nivel_completado;
}
