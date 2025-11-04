#ifndef FONT_HELPERS_H
#define FONT_HELPERS_H

#include "../scene/scene.h"
#include "../entity/entity.h"
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
  
  SDL_Texture* texture;
  i32 width;
  i32 height;
  char text[256];


} TextLabel;



TextLabel * render_text(Scene* scene, TTF_Font *font, const char *message, Color color, TextLabel *self);



#endif 
