#include "map.h"
#include <stdlib.h>

Map *mapa_crear(int w, int h){
    Map *m = malloc(sizeof(Map));
    m->w = w;
    m->h = h;

    m->celdas = malloc(sizeof(int*) * h);

    for(int y=0; y<h; y++){
        m->celdas[y] = malloc(sizeof(int) * w);
        for(int x=0; x<w; x++){
            m->celdas[y][x] = 0;
        }
    }

    return m;
}

void mapa_free(Map *m){
    for(int y=0; y<m->h; y++)
        free(m->celdas[y]);
        free(m->celdas);
        free(m);
}

//TABLERO DE EJEMPLO. NO FINAL!!!!
void mapa_ejemplo(Map *m){
    for(int y=0; y<m->h; y++){
        for(int x=0; x<m->w; x++){
            if(x==0 || y==0 || x==m->w-1 || y==m->h-1)
                m->celdas[y][x] = 2; 
            else if((x + y) % 5 == 0)
                m->celdas[y][x] = 1; 
            else
                m->celdas[y][x] = 0;
        }
    }
}