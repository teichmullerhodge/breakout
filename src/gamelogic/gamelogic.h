#ifndef GAMELOGIC_H 
#define GAMELOGIC_H 

#include <SDL2/SDL.h>
#include "../scene/scene.h"
#include "../entity/entity.h"

void run_game(SDL_Window *win, Scene* scene, Pad* pad, Ball* ball, Brick* bricks);


#endif 

