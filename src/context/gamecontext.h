#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../entity/entity.h"
#include "../helpers/font_helpers.h"

typedef struct
{

  TTF_Font *font;
  TextLabel *player_menu;

  Pad *pad;
  Ball *ball;
  Brick *bricks;

} GameContext;

#endif
