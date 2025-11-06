#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include "appconfig/appconfig.h"
#include <SDL2/SDL_timer.h>
#include <stdint.h>
#include <stdbool.h>
#include "gamelogic/gamelogic.h"
#include "levels/levels.h"
#include "power/power.h"
#include "scene/scene.h"
#include "entity/entity.h"
#include <time.h>
#include<SDL2/SDL_ttf.h>
#include "logger/logger.h"
#include "context/gamecontext.h"
#include <locale.h>



#define N_BRICKS 60

  int main(int argc, char **argv) {

  srand(time(NULL));
  (void)argc;
  (void)argv;
  SDL_Init(SDL_INIT_VIDEO);
  setlocale(LC_ALL, "");

  if (TTF_Init() == -1){
    char error_buffer[2048];
    snprintf(error_buffer, sizeof(error_buffer), "TTF_INIT error: %s\n", TTF_GetError());
    LOGGER_FATAL(error_buffer);
  }

  TTF_Font *game_font = TTF_OpenFont("../font/font.ttf", 24);
  if (game_font == NULL) {
    char error_buffer[2048];
    snprintf(error_buffer, sizeof(error_buffer), "TTF_FONT error: %s\n", TTF_GetError());
    LOGGER_FATAL(error_buffer);
  }

  if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        printf("Error initializing SDL_image: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
  }




  Player player = {"user", 3, 0, 0};

  SDL_Window *win = SDL_CreateWindow("Breakout", 100, 100, APPCONFIG_WINDOW_WIDTH, APPCONFIG_WINDOW_HEIGHT, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  Pad pad = create_pad();
  Ball ball = create_ball();

  Brick bricks[N_BRICKS];
  construct_brick_levels(bricks, sizeof(bricks) / sizeof(bricks)[0], LEVEL_ONE, N_BRICKS);
  Scene *scene = create_scene(renderer);

  TextLabel *player_menu = NULL;
  PowerAssets *power_assets = load_power_assets(scene);
  if(power_assets == NULL) {
    LOGGER_FATAL("Power assets is null. Quiting.");
  }
  GameContext context = {game_font, player_menu, power_assets, &player, &pad, &ball, bricks};
  run_game(win, scene, &context);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  SDL_Quit();
  if (scene != NULL)
    free(scene);
  return 0;
}
