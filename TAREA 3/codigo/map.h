#ifndef MAP_H
#define MAP_H

typedef struct {
    int w, h;
    int **celdas;
} Map;

Map *mapa_crear(int w, int h);
void mapa_free(Map *m);
void mapa_ejemplo(Map *m);

#endif