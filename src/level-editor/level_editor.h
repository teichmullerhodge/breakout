#ifndef LEVEL_EDITOR_H 
#define LEVEL_EDITOR_H 

#include "../scene/scene.h"
#include "../context/gamecontext.h"
#include "../entity/entity.h"
#include <SDL2/SDL.h>

typedef struct {



  bool should_render;
  SDL_Rect rect;


} LevelArea;

typedef struct {

  LevelArea *areas;

} LevelEntities;


void level_editor_mode(SDL_Window *win, Scene *scene, GameContext *context);



#endif 
