#include "scene.h"
#include "../logger/logger.h"


Scene *create_scene(SDL_Renderer *render){
  
  (void)render;
  Scene *sc = malloc(sizeof(Scene));
  if(sc == NULL) { 
    logger_fatal("Could not create an scene. Malloc failed. Check for memory usage.");
  } 

  sc->render = render;
  return sc;

}
