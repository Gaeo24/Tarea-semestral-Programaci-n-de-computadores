#ifndef MAP_H
#define MAP_H

/* map dimensions and tile values */
enum { filas = 11, columnas = 13 };
/*#define C_VACIA 0
#define C_DESTRUCTIBLE 1
#define C_INDESTRUCTIBLE 2
#define C_JUGADOR1 3
#define C_JUGADOR2 4*/

typedef struct {
    int fila;
    int columna;
} Posicion;

extern int mapa[filas][columnas];

#endif 