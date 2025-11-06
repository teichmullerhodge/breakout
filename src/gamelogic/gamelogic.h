#ifndef GAMELOGIC_H 
#define GAMELOGIC_H 

#include <SDL2/SDL.h>
#include "../scene/scene.h"
#include "../entity/entity.h"
#include "../context/gamecontext.h" 

typedef struct {

  bool left_pressed;
  bool right_pressed;
  bool esc_pressed;
  bool p_pressed;
  bool r_pressed;



} GameKeys;

void run_game(SDL_Window *win, Scene* scene, GameContext *context);


#endif 

