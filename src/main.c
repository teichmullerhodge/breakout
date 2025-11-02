#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include "appconfig/appconfig.h" 
#include <SDL2/SDL_timer.h>
#include <stdint.h>
#include <stdbool.h> 
#include "gamelogic/gamelogic.h"
#include "levels/levels.h"
#include "scene/scene.h" 
#include "entity/entity.h"
#include <time.h>

#define N_BRICKS 60

int main(int argc, char **argv) {
  
  srand(time(NULL));
  (void)argc;
  (void)argv;
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window * win = SDL_CreateWindow("Breakout", 100, 100, APPCONFIG_WINDOW_WIDTH, APPCONFIG_WINDOW_HEIGHT, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, 0);

  Pad pad = create_pad();
  Ball ball = create_ball();
  
  Brick bricks[N_BRICKS];
  construct_brick_levels(bricks, sizeof(bricks) / sizeof(bricks)[0], LEVEL_ONE, N_BRICKS);
  Scene *scene = create_scene(renderer);


  run_game(win, scene, &pad, &ball, bricks);


  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  SDL_Quit();
  if(scene != NULL) free(scene);
  return 0;
  
  
}
