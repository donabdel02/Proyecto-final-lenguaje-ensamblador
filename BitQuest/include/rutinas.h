#ifndef RUTINAS_H
#define RUTINAS_H

int contarCaracterMapa(char mapa, int totalceldas, char carcaterBuscado); //funcion para contar moneditas 
int validarMovimiento(char *mapa, int columnas, int fila, int columna); //funcion para validar si el jugador puede moverse a una nueva posicion
int calcularPuntaje(int monedas, int pasos, int nivelesCompletados); //funcion para calcular el puntaje final del jugador basado en las monedas recogidas y los pasos dados
int detectarObjeto(char* mapa, int columnas, int fila, int columna, char objeto); //funcion para detectar en donde hay objetos 
int contarCeladasLibres(char* mapa, int totalceldas); //funcion para detectar camino libre 

#endif // RUTINAS_H