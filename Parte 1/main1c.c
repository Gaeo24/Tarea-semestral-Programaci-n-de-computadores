#include "header1.h"
#include <stdio.h>
#include <stdlib.h>

int **laberinto;
int fil, col;

void printmap(){
    for (int i = 0; i < fil; i++){
        for (int j = 0; j < col; j++){
            printf("%d ", laberinto[i][j]);
        }
        printf("\n");
    }
}

int main(){
    char nombre[200];

    printf("Ingresa el nombre del archivo: ");
    if (scanf("%199s", nombre) != 1) {
        fprintf(stderr, "Error leyendo nombre de archivo\n");
        return 1;
    }

    laberinto = leertxt(nombre, &fil, &col);

    if (laberinto == NULL){
        printf("No se pudo cargar el mapa\n");
        return 1;
    }

    printmap();
    printf("Presiona Enter para continuar...");
    getchar(); // consume newline pendiente
    getchar(); // espera Enter

    espaciopls(laberinto, fil);
    return 0;
}