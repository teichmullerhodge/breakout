#ifndef SCENE_H 
#define SCENE_H 


#include <SDL2/SDL.h>


typedef struct {

  SDL_Renderer * render;

} Scene;


Scene *create_scene(SDL_Renderer *render);
void destroy_scene(Scene *sc);


#endif 
