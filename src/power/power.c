#include "power.h"
#include "../appconfig/appconfig.h"
#include "../logger/logger.h"
#include <SDL2/SDL_image.h>

PowerAssets* load_power_assets(Scene *scene){

  PowerAssets *assets = malloc(sizeof(PowerAssets));
  if(assets == NULL) {
    LOGGER_ERROR("Assets malloc failed at load_power_assets.\n");
    return NULL;
  }

  assets->grow_balls_size = NULL;
  assets->grow_pad = NULL;
  assets->increase_ball_velocity = NULL;
  SDL_Surface * surface = IMG_Load("../assets/star.png");
  if(surface == NULL) {
    LOGGER_ERROR("Error loading image: ");
    LOGGER_ERROR(IMG_GetError());
    free(assets);
    return NULL; 
  }

  assets->increase_pad_velocity = malloc(sizeof(Asset));
  if (!assets->increase_pad_velocity) {
        LOGGER_ERROR("Failed to allocate increase_pad_velocity.\n");
        free(assets);
        return NULL;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(scene->render, surface);
    SDL_FreeSurface(surface);

  if(texture == NULL) {
    LOGGER_ERROR("Error loading texture: ");
    LOGGER_ERROR(SDL_GetError()); 
    free(assets);
    return NULL;
  }

  SDL_Rect *rect = malloc(sizeof(SDL_Rect));
  if(rect == NULL) {
    LOGGER_ERROR("Failed to allocate memory for rect at load_power_assets.\n");
    free(assets->increase_pad_velocity);
    free(assets);
    return NULL;
    
  }

  rect->h = 200;
  rect->w = 200;
  rect->x = 200;
  rect->y = 200;

  assets->increase_pad_velocity->path = NULL; 
  assets->increase_pad_velocity->position = rect;
  assets->increase_pad_velocity->texture = texture; 
  return assets; 
}
