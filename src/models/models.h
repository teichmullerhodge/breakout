#ifndef MODELS_H
#define MODELS_H 

#include <SDL2/SDL.h>


typedef struct {

  const char *path;
  SDL_Rect *position;
  SDL_Texture *texture;


} Asset;


#endif 
