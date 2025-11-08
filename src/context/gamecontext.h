#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../entity/entity.h"
#include "../helpers/font_helpers.h"


typedef struct {

  // data 
  TTF_Font *font;
  TextLabel *player_menu;
  PowerAssets *power_assets;
  Player *player;
  Pad *pad;
  Ball *ball;
  Brick *bricks;

  // state
  LevelMetadata level_info;
  Level current_level;
  size_t bricks_destroyed;
  

} GameContext;

#endif
