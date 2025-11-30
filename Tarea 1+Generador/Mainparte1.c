#include "header1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printmap(){
    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            printf("%d ", mapa[i][j]);
        }
        printf("\n");
    }
}

int main() {

    while (1) {

        int opcion = -1;

        printf("1) Cargar un mapa desde archivo\n");
        printf("2) Generar un mapa nuevo\n");
        printf("0) Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            getchar();
            continue;
        }

        getchar();

        if (opcion == 0) {
            printf("Saliendo...\n");
            return 0;
        }

        if (opcion == 1) {
            char nombre[200];

            printf("Ingrese nombre del archivo:\n> ");
            fgets(nombre, sizeof(nombre), stdin);
            nombre[strcspn(nombre, "\n")] = '\0';

            mapa = leertxt(nombre, &filas, &columnas);
            if (!mapa) {
                printf("Error al cargar archivo. Enter para volver...");
                getchar();
                continue;
            }

            printmap();
            espaciopls(mapa, filas);

            printf("Enter para volver...");
            getchar();
            continue;
        }

        if (opcion == 2) {

            char nombrearchivonuevo[200];
            printf("Nombre del archivo nuevo:\n> ");
            fgets(nombrearchivonuevo, sizeof(nombrearchivonuevo), stdin);
            nombrearchivonuevo[strcspn(nombrearchivonuevo, "\n")] = '\0';

             while (1) {

                printf("Ingrese filas y columnas (minimo 5x5): ");
                char linea[100];

                if (!fgets(linea, sizeof(linea), stdin))
                continue;

                 if (sscanf(linea, "%d %d", &filas, &columnas) != 2) {
                printf("Entrada inválida.\n");
                 continue;
    }

    if (filas >= 5 && columnas >= 5)
        break;

    printf("Dimensiones inválidas.\n");
}

            if (!generar_mapa(nombrearchivonuevo, filas, columnas)) {
                printf("Error al generar mapa. Enter para volver...");
                getchar();
                continue;
            }

            mapa = leertxt(nombrearchivonuevo, &filas, &columnas);
            if (!mapa) {
                printf("Error al cargar mapa generado. Enter para volver...");
                getchar();
                continue;
            }

            printmap();
            espaciopls(mapa, filas);

            printf("Enter para volver...");
            getchar();
            continue;
        }

        printf("Opción invalida.\n");
    }

    return 0;
}
