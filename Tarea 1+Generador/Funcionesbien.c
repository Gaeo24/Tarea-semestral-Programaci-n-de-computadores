#include "header1.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int **mapa = NULL;     
int filas = 0;         
int columnas = 0; 

int **crearmapita(int filas, int columnas) {
    if (filas <= 0 || columnas <= 0) return NULL;

    int **matriz = malloc(filas * sizeof *matriz);
    if (matriz == NULL) {
        fprintf(stderr, "malloc fallo (filas)\n");
        return NULL;
    }

    for (int i = 0; i < filas; i++) {
        matriz[i] = malloc(columnas * sizeof *matriz[i]);
        if (matriz[i] == NULL) {
            fprintf(stderr, "malloc fallo (columnas) en fila %d\n", i);
            for (int k = 0; k < i; k++) free(matriz[k]);
            free(matriz);
            return NULL;
        }
    }
    return matriz;
}

int **leertxt(char *nombretxt, int *filas, int *columnas){
    FILE *txt = fopen(nombretxt, "r");
    if (txt == NULL) {
        fprintf(stderr, "Error al abrir el archivo '%s'\n", nombretxt);
        return NULL;
    }

    if (fscanf(txt, "%d %d", filas, columnas) != 2) {
        fprintf(stderr, "Formato invalido: se esperan dos enteros en la primera linea\n");
        fclose(txt);
        return NULL;
    }

    if (*filas <= 0 || *columnas <= 0) {
        fprintf(stderr, "Las dimensiones deben ser positivas\n");
        fclose(txt);
        return NULL;
    }

    int **matriz = crearmapita(*filas, *columnas);
    if (matriz == NULL) {
        fclose(txt);
        return NULL;
    }

    int tanke = 0, tanke2 = 0;

    for (int i = 0; i < *filas; i++){
        for (int j = 0; j < *columnas; j++){
            int v;
            if (fscanf(txt, "%d", &v) != 1) {
                fprintf(stderr, "Datos insuficientes o formato invalido en la matriz (fila %d col %d)\n", i, j);
                espaciopls(matriz, *filas);
                fclose(txt);
                return NULL;
            }
            if (v < 0 || v > 4) {
                fprintf(stderr, "Valor fuera de rango (%d) en (%d,%d)\n", v, i, j);
                espaciopls(matriz, *filas);
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
        fprintf(stderr, "Solo debe haber un 3 y un 4 en el mapa (encontrados: %d y %d)\n", tanke, tanke2);
        espaciopls(matriz, *filas);
        return NULL;
    }

    for (int j = 0; j < *columnas; j++) {
        if (matriz[0][j] != 2) {
            fprintf(stderr, "Error: La fila superior debe ser solo muros (2).\n");
            espaciopls(matriz, *filas);
            return NULL;
        }
    }

    for (int j = 0; j < *columnas; j++) {
        if (matriz[*filas - 1][j] != 2) {
            fprintf(stderr, "Error: La fila inferior debe ser solo muros (2).\n");
            espaciopls(matriz, *filas);
            return NULL;
        }
    }

    for (int i = 0; i < *filas; i++) {
        if (matriz[i][0] != 2) {
            fprintf(stderr, "Error: La columna izquierda debe ser solo muros (2).\n");
            espaciopls(matriz, *filas);
            return NULL;
        }
    }

    for (int i = 0; i < *filas; i++) {
        if (matriz[i][*columnas - 1] != 2) {
            fprintf(stderr, "Error: La columna derecha debe ser solo muros (2).\n");
            espaciopls(matriz, *filas);
            return NULL;
        }
    }

    mapa = matriz;
    return matriz;
}

void espaciopls(int **matriz, int filas){
    if (matriz == NULL) return;
    for (int i = 0; i < filas; i++){
        free(matriz[i]);
    }
    free(matriz);
}

int generar_mapa(char *archivo, int filas, int columnas) {

    if (filas < 5 || columnas < 5) {
        fprintf(stderr, "El mapa debe ser al menos 5x5.\n");
        return 0;
    }

    srand(time(NULL));

    int **matriz = crearmapita(filas, columnas);
    if (!matriz) {
        fprintf(stderr, "No se pudo crear la matriz.\n");
        return 0;
    }

    for (int j = 0; j < columnas; j++) {
        matriz[0][j] = 2;
        matriz[filas-1][j] = 2;
    }
    for (int i = 0; i < filas; i++) {
        matriz[i][0] = 2;
        matriz[i][columnas-1] = 2;
    }

    for (int i = 1; i < filas-1; i++) {
        for (int j = 1; j < columnas-1; j++) {
            int r = rand() % 100;
            if (r < 70) matriz[i][j] = 0;
            else if (r < 90) matriz[i][j] = 1;
            else matriz[i][j] = 2;
        }
    }

    int x1 = 1 + rand() % (filas - 2);
    int y1 = 1 + rand() % (columnas - 2);
    matriz[x1][y1] = 3;

    int x2, y2;
    do {
        x2 = 1 + rand() % (filas - 2);
        y2 = 1 + rand() % (columnas - 2);
    } while (x1 == x2 && y1 == y2);

    matriz[x2][y2] = 4;

    FILE *txt = fopen(archivo, "w");
    if (!txt) {
        fprintf(stderr, "Error al crear archivo de salida.\n");
        espaciopls(matriz, filas);
        return 0;
    }

    fprintf(txt, "%d %d\n", filas, columnas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++)
            fprintf(txt, "%d ", matriz[i][j]);
        fprintf(txt, "\n");
    }

    fclose(txt);
    espaciopls(matriz, filas);

    fprintf(stdout, "Mapa generado correctamente en '%s'\n", archivo);
    return 1;
}


void esperar_enter() {
    printf("\nPresiona ENTER para salir...");
    getchar(); 
    getchar(); 
}