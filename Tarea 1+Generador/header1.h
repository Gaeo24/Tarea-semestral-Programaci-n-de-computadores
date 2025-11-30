#ifndef PARTE_1
#define PARTE_1

#include <stdio.h>
#include <stdlib.h>

extern int **mapa;
extern int filas;
extern int columnas;

int **crearmapita(int filas, int columnas);
int **leertxt(char *nombretxt, int *filas, int *columnas);
void espaciopls(int **matriz, int filas);
int generar_mapa(char *archivo, int filas, int columnas);
void esperar_enter();
#endif