#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "map.h"
//gcc -o juego.exe Tarea2_main.c map.c
int puntos_j1=0, puntos_j2=0;
int **map=NULL;
Posicion *pos_j=NULL;
int valido(char c);

int valido(char c){
    return (c == 'w' || c == 'a' || c == 's' || c == 'd' || c == 'u' || c == 'h' || c == 'j' || c == 'k' || c == 'e');
}
void validacion_input(char *input){
    if (!valido(*input)){
            do{
                printf("Error, ingrese una jugada valida\n");
                scanf(" %c", input);
            }
            while(!valido(*input));
        }
}
void inicializar_mapa(){
    //Reservar memoria para filas
    map=(int **)malloc(filas*sizeof(int *));
    //Reservar memoria para cada fila
    for (int i=0; i<filas; i++){
        map[i]=(int *)malloc(columnas * sizeof(int));
    }
    for (int i=0; i<filas; i++){
        for (int j=0; j< columnas; j++){
            map[i][j]=mapa[i][j];
        }
    }
    //posicion inicial de los jugadores (3=J1; 4=J2)
    pos_j= malloc(2*sizeof(Posicion));
    for(int i=0; i<filas; i++){
        for(int j=0; j<columnas; j++){
            if (map[i][j]==3){
                pos_j[0].fila=i;
                pos_j[0].columna=j;
            }
            else if(map[i][j]==4){
                pos_j[1].fila=i;
                pos_j[1].columna=j;
            }
        }
    }
}
void liberar_mapa(){
    for (int i=0; i<filas; i++){
        free(map[i]);
    }
    free(map);
    free(pos_j);
}
void reiniciar_mapa(){
    for (int i=0; i<filas; i++){
        for (int j=0; j< columnas; j++){
            map[i][j]=mapa[i][j];
            if (map[i][j]==3){
                pos_j[0].fila=i;
                pos_j[0].columna=j;
            }
            else if(map[i][j]==4){
                pos_j[1].fila=i;
                pos_j[1].columna=j;
            }
        }
    }
}
void printmap(){
    for (int i=0; i<filas; i++){
        for (int j=0; j<columnas; j++){
            printf("%d", map[i][j]);
        }
    printf("\n");
    }
}
void movimiento(char input, int jugador, int i){
    int f=pos_j[jugador].fila;
    int c=pos_j[jugador].columna;

    if (input=='w' && map[f-1][c]==0 && f-1>=0){
        map[f][c]=0;
        map[f-1][c]=i;
        pos_j[jugador].fila--;
    }
    else if (input=='a' && map[f][c-1]==0 && c-1>=0){
        map[f][c]=0;
        map[f][c-1]=i;
        pos_j[jugador].columna--;
    }
    else if (input=='s' && map[f+1][c]==0 && f+1<filas){
        map[f][c]=0;
        map[f+1][c]=i;
        pos_j[jugador].fila++;
    }
    else if (input=='d' && map[f][c+1]==0 && c+1<columnas){
        map[f][c]=0;
        map[f][c+1]=i;
        pos_j[jugador].columna++;
    }
    
}
void disparo(char input, int jugador){
    int f=pos_j[jugador].fila;
    int c=pos_j[jugador].columna;
    int vf=0, vc=0; //vf y vc son "vectores" 
    int desplazamiento=1;

    if (input=='u') vf=-1;
    else if (input=='h') vc=-1;
    else if (input=='j') vf=1;
    else if (input=='k') vc=1;

    while (f+vf*desplazamiento>=0 && f+vf*desplazamiento<filas && c+vc*desplazamiento>=0 && c+vc*desplazamiento<columnas){
        int nuevaf= f+vf*desplazamiento;
        int nuevac= c+vc*desplazamiento;
        if (map[nuevaf][nuevac]==1){
            map[nuevaf][nuevac]=0;
            break;
        }
        else if(map[nuevaf][nuevac]==2){
            break;
        }
        else if(map[nuevaf][nuevac]==3){
            map[nuevaf][nuevac]=0;
            printf("Jugador 1 destruido\n");
            puntos_j2++;
            reiniciar_mapa();
            break;
        }
        else if(map[nuevaf][nuevac]==4){
            map[nuevaf][nuevac]=0;
            printf("Jugador 2 destruido\n");
            puntos_j1++;
            reiniciar_mapa();
            break;
        }
        desplazamiento++;        
    }
}
void seleccion_jugada(char input, int j, int i){
        if(input=='w'||input=='a'||input=='s'||input=='d'){
            movimiento(input, j, i);
        }
        else if(input=='u'||input=='h'||input=='j'||input=='k'){
            disparo(input,j);
        }
}
void resultado_final(){
    if (puntos_j1>puntos_j2){
        printf("Jugador 1 gana con %d puntos!\n", puntos_j1);
    }
    else if (puntos_j2>puntos_j1){
        printf("Jugador 2 gana con %d puntos!\n", puntos_j2);
    }
    else{
        printf("Empate con %d puntos cada uno!\n", puntos_j1);
    }
}
int main(){
    int turno=1;
    char input;

    inicializar_mapa();
    printmap();

    while (turno<=300) {
        printf("Turno N°%d del jugador 1\n", turno);
        scanf(" %c", &input); //(w/a/s/d) para moverse (u/h/j/k) para disparar
        input=tolower(input);
        validacion_input(&input);
        if (input == 'e'){ //e de exit
            break;
        }
        seleccion_jugada(input, 0, 3);
        printmap();
        if (puntos_j1>=3){
            printf("Jugador 1 gana con %d puntos!\n", puntos_j1);
            break;
        }

        printf("Turno N°%d del jugador 2\n", turno);
        scanf(" %c", &input); //(w/a/s/d) para moverse (u/h/j/k) para disparar
        input=tolower(input);
        validacion_input(&input);
        if (input == 'e'){ //e de exit
            break;
        }    
        seleccion_jugada(input, 1, 4);
        printmap();
        if (puntos_j2>=3){
            printf("Jugador 2 gana con %d puntos!\n", puntos_j2);
            break;
        }
        turno++;
    }
    if (turno>=300){
        printf("Se alcanzó el límite de turnos.\n");
        resultado_final();
        printf("Pulse cualquier tecla y luego Enter para salir...\n");
        char c;
        scanf(" %c", &c);
    }
    if (puntos_j1>=3 || puntos_j2>=3){
        printf("Pulse cualquier tecla y luego Enter para salir...\n");
        char c;
        scanf(" %c", &c);
    }
    liberar_mapa();
    return 0;
}