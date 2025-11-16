#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "visual.h"

SDL_Texture *load_texture(SDL_Renderer *ren, const char *path){
    SDL_Surface *surf = IMG_Load(path);

    if(!surf){
        printf("IMG_Load '%s': %s\n", path, IMG_GetError());
        return NULL;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_FreeSurface(surf);

    return tex;
}

int visual_init(Visual *v, const char *title, int width, int height){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0){
        printf("SDL_Init error: %s\n", SDL_GetError());
        return 0;
    }

    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
        printf("IMG_Init PNG error: %s\n", IMG_GetError());
    }

    v->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    v->ren = SDL_CreateRenderer(v->win, -1, SDL_RENDERER_ACCELERATED);

    return (v->win && v->ren);
}

int visual_cargar_assets(Visual *v){
    char *base_path = SDL_GetBasePath();
    char fullpath[512];

    // Ladrillo
    sprintf(fullpath, "%s../assets/tiles/IndustrialTile_46.png", base_path);
    v->tex_brick = load_texture(v->ren, fullpath);

    // Metal
    sprintf(fullpath, "%s../assets/tiles/IndustrialTile_65.png", base_path);
    v->tex_metal = load_texture(v->ren, fullpath);

    // Tanque azul
    sprintf(fullpath, "%s../assets/tanques/tank_blue.png", base_path);
    v->tex_tank_blue = load_texture(v->ren, fullpath);

    // Tanque rojo
    sprintf(fullpath, "%s../assets/tanques/tank_red.png", base_path);
    v->tex_tank_red = load_texture(v->ren, fullpath);

    // ------------------------------------------------
    // CARGAR LOS 64 FRAMES DE EXPLOSIÓN INDIVIDUALES
    // ------------------------------------------------
    v->expl_frames_total = 0;

    for (int i = 0; i < 64; i++) {

        sprintf(fullpath, "%s../assets/explosiones/frame%04d.png", base_path, i);

        SDL_Texture *tmp = load_texture(v->ren, fullpath);

        if (!tmp) {
            printf("No se pudo cargar: %s\n", fullpath);
            break;
        }

        v->tex_expl_frames[i] = tmp;
        v->expl_frames_total++;
    }

    printf("Frames de explosión cargados: %d\n", v->expl_frames_total);

    SDL_free(base_path);

    return (v->tex_brick && v->tex_metal && v->tex_tank_blue && v->expl_frames_total > 0);
}

void visual_cerrar(Visual *v){
    SDL_DestroyTexture(v->tex_brick);
    SDL_DestroyTexture(v->tex_metal);
    SDL_DestroyTexture(v->tex_tank_blue);
    SDL_DestroyTexture(v->tex_tank_red);

    // Destruir frames de explosión
    for (int i = 0; i < v->expl_frames_total; i++)
        SDL_DestroyTexture(v->tex_expl_frames[i]);

    SDL_DestroyRenderer(v->ren);
    SDL_DestroyWindow(v->win);

    IMG_Quit();
    SDL_Quit();
}

void visual_render(Map *m, Visual *v, int tile_size,
                   int expl1_frame,
                   int expl2_frame,
                   int tank1_x, int tank1_y, int tank1_angle,
                   int tank2_x, int tank2_y, int tank2_angle)
{
    SDL_Renderer *ren = v->ren;

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    SDL_Rect dst;

    // Dibujar tiles
    for(int y=0; y<m->h; y++){
        for(int x=0; x<m->w; x++){

            dst.x = x * tile_size;
            dst.y = y * tile_size;
            dst.w = tile_size;
            dst.h = tile_size;

            if(m->celdas[y][x] == 1)
                SDL_RenderCopy(ren, v->tex_brick, NULL, &dst);
            else if(m->celdas[y][x] == 2)
                SDL_RenderCopy(ren, v->tex_metal, NULL, &dst);
        }
    }

    // Dibujar tanques
    SDL_Rect t1dst = { tank1_x * tile_size, tank1_y * tile_size, tile_size, tile_size };
    SDL_RenderCopyEx(ren, v->tex_tank_blue, NULL, &t1dst,
                 tank1_angle, NULL, SDL_FLIP_NONE);

    SDL_Rect t2dst = { tank2_x * tile_size, tank2_y * tile_size, tile_size, tile_size };
    SDL_RenderCopyEx(ren, v->tex_tank_red, NULL, &t2dst,
                 tank2_angle, NULL, SDL_FLIP_NONE);

    // -------------------------
    // EXPLOSIÓN 1
    // -------------------------
    if (expl1_frame >= 0 && expl1_frame < v->expl_frames_total) {

        SDL_Rect ddst = {
            t1dst.x - tile_size/2,
            t1dst.y - tile_size/2,
            tile_size * 2,
            tile_size * 2
        };

        SDL_RenderCopy(ren, v->tex_expl_frames[expl1_frame], NULL, &ddst);
    }

    // -------------------------
    // EXPLOSIÓN 2
    // -------------------------
    if (expl2_frame >= 0 && expl2_frame < v->expl_frames_total) {

        SDL_Rect ddst = {
            t2dst.x - tile_size/2,
            t2dst.y - tile_size/2,
            tile_size * 2,
            tile_size * 2
        };

        SDL_RenderCopy(ren, v->tex_expl_frames[expl2_frame], NULL, &ddst);
    }

    SDL_RenderPresent(ren);
}
