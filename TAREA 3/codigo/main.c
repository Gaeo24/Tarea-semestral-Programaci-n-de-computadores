#include <SDL2/SDL.h>
#include "map.h"
#include "visual.h"


void get_direction(int ang, int *vx, int *vy) {
    *vx = 0;
    *vy = 0;
    if (ang == 0) *vx = 1;      
    else if (ang == 180) *vx = -1; 
    else if (ang == 270) *vy = -1; 
    else if (ang == 90) *vy = 1;   
}

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

    int tank1_ang = 0;
    int tank2_ang = 0;

    
    int explosion_frame = -1;      
    Uint32 sig_frame_time = 0;

    
    int expl2_frame = -1;
    Uint32 expl2_sig_time = 0;

    Uint32 frame_delay = 80;

    
    bala bala1 = {0, 0, 0, 0, 0, 0, 0};
    bala bala2 = {0, 0, 0, 0, 0, 0, 0};

    
    Uint32 bala_update = 0; 
    Uint32 bala_update_delay = 80;


    while(running){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT)
                running = 0;

            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_ESCAPE: running = 0; break;
                    
                    
                    case SDLK_a: 
                        tank1_x--; 
                        tank1_ang = 180; 
                        break;
                    case SDLK_d:
                        tank1_x++; 
                        tank1_ang = 0; 
                        break;
                    case SDLK_w:   
                        tank1_y--; 
                        tank1_ang = 270; 
                        break;
                    case SDLK_s: 
                        tank1_y++; 
                        tank1_ang = 90;
                        break;
                    

                    case SDLK_SPACE:
                        
                        if (!bala1.activa) {
                            bala1.activa = 1;
                            bala1.x = tank1_x;
                            bala1.y = tank1_y;
                            get_direction(tank1_ang, &bala1.vx, &bala1.vy);
                            explosion_frame = -1;
                        }
                        break;

                    
                    case SDLK_LEFT:    
                        tank2_x--; 
                        tank2_ang = 180;
                        break;
                    case SDLK_RIGHT:    
                        tank2_x++; 
                        tank2_ang = 0; 
                        break;
                    case SDLK_UP:    
                        tank2_y--; 
                        tank2_ang = 270;
                        break;
                    case SDLK_DOWN:    
                        tank2_y++; 
                        tank2_ang = 90;
                        break;
                    

                    case SDLK_RETURN: 
                        
                        if (!bala2.activa) {
                            bala2.activa = 1;
                            bala2.x = tank2_x;
                            bala2.y = tank2_y;
                            get_direction(tank2_ang, &bala2.vx, &bala2.vy);
                            expl2_frame = -1;
                        }
                        break;
                }
            }
        }

        
        if (SDL_GetTicks() >= bala_update + bala_update_delay) {
            
            
            if (bala1.activa) {
                int sig_x = bala1.x + bala1.vx;
                int sig_y = bala1.y + bala1.vy;
                int colision = 0;
                
               
                if (sig_x < 0 || sig_x >= W || sig_y < 0 || sig_y >= H) {
                    colision = 1; 
                } else if (m->celdas[sig_y][sig_x] != 0) {
                    colision = 1; 
                }

                
                if (sig_x == tank2_x && sig_y == tank2_y) {
                    colision = 1;
                }


                if (colision) {
                    explosion_frame = 0;
                    sig_frame_time = SDL_GetTicks() + frame_delay;
                    
                    bala1.expl_x = sig_x; 
                    bala1.expl_y = sig_y;
                    
                    bala1.activa = 0;

                } else {
                    bala1.x = sig_x;
                    bala1.y = sig_y;
                }
            }
            
            
            if (bala2.activa) {
                int sig_x = bala2.x + bala2.vx;
                int sig_y = bala2.y + bala2.vy;
                int colision = 0;

                
                if (sig_x < 0 || sig_x >= W || sig_y < 0 || sig_y >= H) {
                    colision = 1;
                } else if (m->celdas[sig_y][sig_x] != 0) {
                    colision = 1;
                }
                
                
                if (sig_x == tank1_x && sig_y == tank1_y) {
                    colision = 1;
                }


                if (colision) {
                    expl2_frame = 0;
                    expl2_sig_time = SDL_GetTicks() + frame_delay;
                    
                    bala2.expl_x = sig_x;
                    bala2.expl_y = sig_y;
                    
                    bala2.activa = 0;

                } else {
                    bala2.x = sig_x;
                    bala2.y = sig_y;
                }
            }

            bala_update = SDL_GetTicks();
        }


        
        if (explosion_frame >= 0) {
            if (SDL_GetTicks() >= sig_frame_time) {

                explosion_frame++;  
                sig_frame_time = SDL_GetTicks() + frame_delay;

                if (explosion_frame >= vis.expl_frames_total)
                    explosion_frame = -1; 
            }
        }


        
        if (expl2_frame >= 0) {
            if (SDL_GetTicks() >= expl2_sig_time) {

                expl2_frame++;
                expl2_sig_time = SDL_GetTicks() + frame_delay;

                if (expl2_frame >= vis.expl_frames_total)
                    expl2_frame = -1;
            }
        }

    
        visual_render(m, &vis, TILE, 
              explosion_frame, 
              expl2_frame,
              tank1_x, tank1_y, tank1_ang, 
              tank2_x, tank2_y, tank2_ang,
              &bala1, &bala2);

        SDL_Delay(16);
    }

    visual_cerrar(&vis);
    mapa_free(m);

    return 0;
}