// ============================================================
// main.c - Punto de entrada del juego BitQuest
// BitQuest: Explorador de Matrices con C y NASM
// ============================================================

#include "juego.h"
#include "mapas.h"

// ============================================================
// mostrar_menu
// Muestra el menu principal del juego y retorna la opcion
// elegida por el usuario.
// ============================================================
static void mostrar_menu(void) {
    limpiar_pantalla();
    printf("\n\n");
    printf("  ############################################################\n");
    printf("  #                                                          #\n");
    printf("  #    BBBBB  IIIII TTTTT  QQQ  U   U EEEEE  SSS  TTTTT    #\n");
    printf("  #    B   B    I     T   Q   Q U   U E     S       T       #\n");
    printf("  #    BBBB     I     T   Q   Q U   U EEE    SSS    T       #\n");
    printf("  #    B   B    I     T   Q  QQ U   U E         S   T       #\n");
    printf("  #    BBBBB  IIIII   T    QQQ Q  UUU  EEEEE SSSS    T      #\n");
    printf("  #                                                          #\n");
    printf("  #         Explorador de Matrices con C y NASM             #\n");
    printf("  #                                                          #\n");
    printf("  ############################################################\n");
    printf("\n");
    printf("  Leyenda del mapa:\n");
    printf("    \033[1;32mP\033[0m = Jugador    \033[1;34m#\033[0m = Pared     \033[1;33mM\033[0m = Moneda\n");
    printf("    \033[1;36mK\033[0m = Llave      \033[1;31mD\033[0m = Puerta    \033[1;35mE\033[0m = Salida\n");
    printf("\n");
    printf("  Controles: W = Arriba   S = Abajo   A = Izquierda   D = Derecha\n");
    printf("             Q = Salir del juego\n");
    printf("\n");
    printf("  Objetivo: Recolecta monedas, encuentra la llave,\n");
    printf("            abre la puerta y llega a la salida.\n\n");
    printf("  Presiona ENTER para comenzar...\n\n");
    fflush(stdout);
    getchar();
}

// ============================================================
// main
// Funcion principal: muestra menu, ejecuta los 3 niveles y
// muestra el resumen final con el puntaje calculado en NASM.
// ============================================================
int main(void) {
    // Copias de trabajo de los mapas (los originales son const en mapas.h)
    // Se necesitan copias porque el juego modifica el mapa (quita monedas, etc.)
    char nivel1[FILAS_MAPA][COLS_MAPA];
    char nivel2[FILAS_MAPA][COLS_MAPA];
    char nivel3[FILAS_MAPA][COLS_MAPA];

    memcpy(nivel1, mapa1, sizeof(mapa1));
    memcpy(nivel2, mapa2, sizeof(mapa2));
    memcpy(nivel3, mapa3, sizeof(mapa3));

    // Estado del jugador (acumulado a lo largo de todos los niveles)
    Jugador jugador;
    memset(&jugador, 0, sizeof(Jugador));

    // Mostrar pantalla de inicio
    mostrar_menu();

    // Array de punteros a los mapas para iterar facilmente
    char (*mapas[NUM_NIVELES])[COLS_MAPA] = { nivel1, nivel2, nivel3 };

    int total_monedas_global = 0;

    // --- Calcular total de monedas de todos los niveles con NASM ---
    total_monedas_global += (int)contar_caracter((char*)mapa1, FILAS_MAPA*COLS_MAPA, CHAR_MONEDA);
    total_monedas_global += (int)contar_caracter((char*)mapa2, FILAS_MAPA*COLS_MAPA, CHAR_MONEDA);
    total_monedas_global += (int)contar_caracter((char*)mapa3, FILAS_MAPA*COLS_MAPA, CHAR_MONEDA);

    // --- Bucle principal de niveles ---
    for (int n = 0; n < NUM_NIVELES; n++) {
        iniciar_nivel(mapas[n], &jugador);

        int resultado = jugar_nivel(mapas[n], &jugador, n + 1);

        if (!resultado) {
            // El jugador eligio salir (Q)
            limpiar_pantalla();
            printf("\n  Juego terminado. Hasta la proxima!\n\n");
            return 0;
        }
    }

    // --- Calcular puntaje final con NASM ---
    long puntaje = calcular_puntaje(
        (long)jugador.monedas_total,
        (long)jugador.pasos_total,
        (long)NUM_NIVELES
    );

    // --- Mostrar resumen final ---
    mostrar_resumen_final(
        jugador.monedas_total,
        total_monedas_global,
        jugador.pasos_total,
        (int)puntaje
    );

    printf("  Presiona ENTER para salir...\n");
    getchar();

    return 0;
}
