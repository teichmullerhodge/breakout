#ifndef GAMELOGIC_H 
#define GAMELOGIC_H 

#include <SDL2/SDL.h>
#include "../scene/scene.h"
#include "../entity/entity.h"
#include "../context/gamecontext.h" 


void run_game(SDL_Window *win, Scene* scene, GameContext *context);


#endif 

