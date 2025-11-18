#include "header1.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    int **laberinto;
    int fil,col;
    char nombre[200];

    printf("Ingresa el nombre del archivo: ");
    scanf("%s",nombre);

laberinto=leertxt(nombre,&fil,&col);

if(laberinto==NULL){
printf("No se pudo cargar el mapa\n");
return 1;
}

espaciopls(laberinto,fil);

return 0;
}