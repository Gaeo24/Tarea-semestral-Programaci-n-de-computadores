#ifndef VISUAL_H
#define VISUAL_H

#include "map.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


typedef struct {
    int activa;  
    int x, y;    
    int vx, vy;  
    int expl_x, expl_y; 
} bala;

typedef struct {
    SDL_Window *win;
    SDL_Renderer *ren;  

    SDL_Texture *tex_brick;
    SDL_Texture *tex_metal;
    SDL_Texture *tex_tank_blue;
    SDL_Texture *tex_tank_red;

    SDL_Texture *tex_expl_frames[64];
    int expl_frames_total;
} Visual;

int visual_init(Visual *v, const char *title, int width, int height);
void visual_cerrar(Visual *v);
int visual_cargar_assets(Visual *v);


void visual_render(Map *m, Visual *v, int tile_size,
                       int expl1_frame,
                       int expl2_frame,
                       int tank1_x, int tank1_y, int tank1_angle,
                       int tank2_x, int tank2_y, int tank2_angle,
                       bala *bala1, bala *bala2);

SDL_Texture *load_texture(SDL_Renderer *ren, const char *path);

#endif