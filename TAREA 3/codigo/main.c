#include <SDL2/SDL.h>
#include "map.h"
#include "visual.h"

int main(int argc, char *argv[]){

    const int TILE = 32;
    const int W = 15, H = 13;

    Map *m = mapa_crear(W,H);
    mapa_ejemplo(m);

    Visual vis;
    if(!visual_init(&vis, "Battle City", W*TILE, H*TILE))
        return 1;

    if(!visual_cargar_assets(&vis))
        return 1;

    int running = 1;
    SDL_Event e;

    int tank1_x = 2, tank1_y = 2;
    int tank2_x = W - 3, tank2_y = H - 3;

    int tank1_angle = 0;
    int tank2_angle = 0;

    int explosion_frame = -1;      
    Uint32 next_frame_time = 0;

    int expl2_frame = -1;
    Uint32 expl2_next_time = 0;

    Uint32 frame_delay = 80;

    while(running){
        while(SDL_PollEvent(&e)){
            // CORRECCIÓN: SDL_EVENT_QUIT -> SDL_QUIT (para SDL2)
            if(e.type == SDL_QUIT)
                running = 0;

            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_ESCAPE: running = 0; break;
                    case SDLK_LEFT: tank1_x--;
                                    tank1_angle = 180; 
                                    break;
                    case SDLK_RIGHT:tank1_x++;
                                    tank1_angle = 0; 
                                    break;
                    case SDLK_UP:   tank1_y--;
                                    tank1_angle = 270; 
                                    break;
                    case SDLK_DOWN: tank1_y++;
                                    tank1_angle = 90;
                                    break;

                    case SDLK_SPACE:
                        explosion_frame = 0;
                        // SDL_GetTicks() sigue siendo válido en SDL2
                        next_frame_time = SDL_GetTicks() + frame_delay;
                        break;

                    case SDLK_a:    tank2_x--; 
                                    tank2_angle = 180;
                                    break;
                    case SDLK_d:    tank2_x++;
                                    tank2_angle = 0; 
                                    break;
                    case SDLK_w:    tank2_y--; 
                                    tank2_angle = 270;
                                    break;
                    case SDLK_s:    tank2_y++;
                                    tank2_angle = 90;
                                    break;

                    case SDLK_RETURN: // Tecla ENTER para disparar el P2
                        expl2_frame = 0; // Disparo del P2
                        expl2_next_time = SDL_GetTicks() + frame_delay;
                        break;
                }
            }
        }

        // EXPLOSIÓN 1
        if (explosion_frame >= 0) {
            if (SDL_GetTicks() >= next_frame_time) {

                explosion_frame++;  
                next_frame_time = SDL_GetTicks() + frame_delay;

                if (explosion_frame >= vis.expl_frames_total)
                    explosion_frame = -1;  // explosion terminada
            }
        }


        // EXPLOSIÓN 2
        if (expl2_frame >= 0) {
            if (SDL_GetTicks() >= expl2_next_time) {

                expl2_frame++;
                expl2_next_time = SDL_GetTicks() + frame_delay;

                if (expl2_frame >= vis.expl_frames_total)
                    expl2_frame = -1;
            }
        }

        visual_render(m, &vis, TILE, 
              explosion_frame, 
              expl2_frame,
              tank1_x, tank1_y, tank1_angle, 
              tank2_x, tank2_y, tank2_angle);

        SDL_Delay(16);
    }

    visual_cerrar(&vis);
    mapa_free(m);

    return 0;
}