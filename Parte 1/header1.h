#ifndef PARTE_1
#define PARTE_1

#include <stdio.h>
#include <stdlib.h>
//para parte 2
extern int **mapa;
extern int filas;
extern int columnas;


int **crearmapita(int fil, int col);
int **leertxt(char *nombretxt,int *fil,int *col);
void espaciopls(int **matriz,int fil);

#endif 