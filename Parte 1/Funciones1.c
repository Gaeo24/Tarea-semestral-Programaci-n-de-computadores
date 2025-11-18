#include "header1.h"
#include <stdio.h>
#include <stdlib.h>


int **mapa = NULL;
int filas = 0;
int columnas = 0;


//crear espacio en el mapa
int **crearmapita(int fil, int col) {
int **matriz=malloc(fil*sizeof(int*));
if(matriz==NULL){
    printf("Error con la memoria\n");
    return NULL;
}


for(int i=0;i<fil;i++){
matriz[i]=malloc(col*sizeof(int));
if(matriz[i]==NULL){
    printf("Error con la memoria\n");
    for (int k=0;k<i;k++) 
    free(matriz[k]);
    free(matriz);
    return NULL;
}
}

return matriz;
}


//leer y validar cosas basicas del mapa en el txt ingresado

int **leertxt(char *nombretxt,int *fil,int *col){
FILE *txt=fopen(nombretxt, "r");
if(txt==NULL){
printf("Error al abrir el archivo '%s'\n",nombretxt);
return NULL;
}

if (fscanf(txt,"%d %d",fil,col)!=2){
    printf("Error al ingresar dimensiones\n");
    fclose(txt);
    return NULL;
}

if(*fil<=0 || *col<=0){
printf("Las dimensiones deben ser positivas\n");
fclose(txt);
return NULL;
}

int **matriz= crearmapita(*fil, *col);

if(matriz== NULL){
fclose(txt);
return NULL;
}


int valorenesepunto,tanke=0,tanke2=0;

for(int i=0;i<*fil;i++){
    for(int j=0;j<*col;j++){
    if(fscanf(txt,"%d",&valorenesepunto)!=1){
        printf("Falta valor en la posicion (%d,%d)\n",i,j);
        espaciopls(matriz,*fil);
        fclose(txt);
        return NULL;
    }
    
    if(valorenesepunto<0 || valorenesepunto>4){
        printf("El valor en la matriz debe estar entre 0 y 4\n");
        espaciopls(matriz,*fil);
        fclose(txt);
        return NULL;
    }
    if(valorenesepunto==3){
        tanke+=1;

    }
    if(valorenesepunto==4){
        tanke2+=1;

    }
matriz[i][j] = valorenesepunto;
}
}
fclose(txt);

if(tanke!=1 || tanke2!=1){
printf("Solo puede haber dos tanques (Cambiar el 3 y 4 en la matriz )\n");
espaciopls(matriz,*fil);
return NULL;
}

for (int j = 0; j < *col; j++) {
    if (matriz[0][j] != 2) {
        printf("Error: La fila superior debe estar compuesta solo por muros (2).\n");
        espaciopls(matriz, *fil);
        return NULL;
    }
}


for (int j = 0; j < *col; j++) {
    if (matriz[*fil - 1][j] != 2) {
        printf("Error: La fila inferior debe estar compuesta solo por muros (2).\n");
        espaciopls(matriz, *fil);
        return NULL;
    }
}


for (int i = 0; i < *fil; i++) {
    if (matriz[i][0] != 2) {
        printf("Error: La columna izquierda debe estar compuesta solo por muros (2).\n");
        espaciopls(matriz, *fil);
        return NULL;
    }
}


for (int i = 0; i < *fil; i++) {
    if (matriz[i][*col - 1] != 2) {
        printf("Error: La columna derecha debe estar compuesta solo por muros (2).\n");
        espaciopls(matriz, *fil);
        return NULL;
    }
}
//para parte 2
mapa = matriz;
filas = *fil;
columnas = *col;

return matriz;
}

//liberar en caso de falla
void espaciopls(int **matriz,int fil){
if(matriz==NULL){
    return;
}
for(int i=0;i<fil;i++){
    free(matriz[i]);
}
free(matriz);
}

