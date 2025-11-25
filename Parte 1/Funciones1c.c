#include "header1.h"
#include <stdio.h>
#include <stdlib.h>

int **mapa = NULL;
int filas = 0;
int columnas = 0;

int **crearmapita(int fil, int col) {
    int **matriz = malloc(fil * sizeof *matriz);
    if (matriz == NULL) {
        fprintf(stderr, "malloc fallo (filas)\n");
        return NULL;
    }

    for (int i = 0; i < fil; i++) {
        matriz[i] = malloc(col * sizeof *matriz[i]);
        if (matriz[i] == NULL) {
            fprintf(stderr, "malloc fallo (columnas) en fila %d\n", i);
            for (int k = 0; k < i; k++) free(matriz[k]);
            free(matriz);
            return NULL;
        }
    }
    return matriz;
}

int **leertxt(char *nombretxt,int *fil,int *col){
    FILE *txt = fopen(nombretxt, "r");
    if (txt == NULL) {
        fprintf(stderr, "Error al abrir el archivo '%s'\n", nombretxt);
        return NULL;
    }

    if (fscanf(txt, "%d %d", fil, col) != 2) {
        fprintf(stderr, "Formato invalido: se esperan dos enteros en la primera linea\n");
        fclose(txt);
        return NULL;
    }

    if (*fil <= 0 || *col <= 0) {
        fprintf(stderr, "Las dimensiones deben ser positivas\n");
        fclose(txt);
        return NULL;
    }

    int **matriz = crearmapita(*fil, *col);
    if (matriz == NULL) {
        fclose(txt);
        return NULL;
    }

    int tanke = 0, tanke2 = 0;
    for (int i = 0; i < *fil; i++){
        for (int j = 0; j < *col; j++){
            int v;
            if (fscanf(txt, "%d", &v) != 1) {
                fprintf(stderr, "Datos insuficientes o formato invalido en la matriz (fila %d col %d)\n", i, j);
                espaciopls(matriz, *fil);
                fclose(txt);
                return NULL;
            }
            matriz[i][j] = v;
            if (v == 3) tanke++;
            if (v == 4) tanke2++;
        }
    }
    fclose(txt);

    if (tanke != 1 || tanke2 != 1) {
        fprintf(stderr, "Solo puede haber un 3 y un 4 en el mapa (encontrados: %d y %d)\n", tanke, tanke2);
        espaciopls(matriz, *fil);
        return NULL;
    }

    // opcionales: validaciones por filas/columnas (se pueden añadir aquí)

    // para parte 2
    mapa = matriz;
    filas = *fil;
    columnas = *col;

    return matriz;
}

void espaciopls(int **matriz,int fil){
    if (matriz == NULL) return;
    for (int i = 0; i < fil; i++){
        free(matriz[i]);
    }
    free(matriz);
}

