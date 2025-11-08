#include "power.h"
#include "../appconfig/appconfig.h"
#include "../logger/logger.h"
#include <SDL2/SDL_image.h>

SDL_Surface *load_image(const char *path) {

  SDL_Surface *surface = IMG_Load(path);
  if(surface == NULL) {
    LOGGER_ERROR("Error loading image: ");
    LOGGER_ERROR(IMG_GetError());
    return NULL; 
  }

  return surface;

}

// is this the best way to do this?
PowerAssets* load_power_assets(Scene *scene){

  PowerAssets *assets = malloc(sizeof(PowerAssets));
  if(assets == NULL) {
    LOGGER_ERROR("Assets malloc failed at load_power_assets.\n");
    return NULL;
  }

  assets->grow_pad = NULL;
  assets->grow_balls_size = NULL;
  assets->increase_pad_velocity = NULL;
  assets->increase_ball_velocity = NULL;

  SDL_Surface *grow_pad_surface = load_image("../assets/pow-grow-pad.png");
  if(grow_pad_surface == NULL) {
    free(assets);
    return NULL;
  }
  SDL_Surface *grow_balls_surface = load_image("../assets/pow-grow-ball.png");
  if(grow_pad_surface == NULL) {
    SDL_FreeSurface(grow_pad_surface);
    free(assets);
    
    return NULL;
  }

  SDL_Surface *increase_pad_velocity_surface = load_image("../assets/pow-pad-velocity.png");
  if(grow_pad_surface == NULL) {
    SDL_FreeSurface(grow_pad_surface);
    SDL_FreeSurface(grow_balls_surface); 
    free(assets);
    return NULL;
  }

  SDL_Surface *increase_ball_velocity_surface = load_image("../assets/pow-ball-velocity.png");
  if(increase_ball_velocity_surface == NULL) {
    SDL_FreeSurface(grow_pad_surface);
    SDL_FreeSurface(grow_balls_surface); 
    SDL_FreeSurface(increase_pad_velocity_surface);  
    free(assets);
    return NULL;
  }

  assets->increase_pad_velocity = malloc(sizeof(Asset));
  if (assets->increase_pad_velocity == NULL) {
        LOGGER_ERROR("Failed to allocate increase_pad_velocity asset.\n");
        free(assets);
        SDL_FreeSurface(grow_pad_surface);
        SDL_FreeSurface(grow_balls_surface); 
        SDL_FreeSurface(increase_pad_velocity_surface);  
        SDL_FreeSurface(increase_ball_velocity_surface);
        return NULL;
  }

  assets->grow_pad = malloc(sizeof(Asset));
  if (assets->grow_pad == NULL) {
        LOGGER_ERROR("Failed to allocate grow_pad asset.\n");
        free(assets->increase_pad_velocity);
        free(assets);
        SDL_FreeSurface(grow_pad_surface);
        SDL_FreeSurface(grow_balls_surface); 
        SDL_FreeSurface(increase_pad_velocity_surface);  
        SDL_FreeSurface(increase_ball_velocity_surface); 
        return NULL;
  }
  assets->grow_balls_size = malloc(sizeof(Asset));
  if (assets->grow_balls_size == NULL) {
        LOGGER_ERROR("Failed to allocate grow_balls_size asset.\n");
        free(assets->increase_pad_velocity);
        free(assets->grow_pad);
        free(assets);
        SDL_FreeSurface(grow_pad_surface);
        SDL_FreeSurface(grow_balls_surface); 
        SDL_FreeSurface(increase_pad_velocity_surface);  
        SDL_FreeSurface(increase_ball_velocity_surface); 
        return NULL;
  }

  assets->increase_ball_velocity = malloc(sizeof(Asset));
  if (assets->increase_ball_velocity == NULL) {
        LOGGER_ERROR("Failed to allocate increase_ball_velocity asset.\n");
        free(assets->increase_pad_velocity);
        free(assets->grow_pad);
        free(assets->grow_balls_size);
        free(assets);
        SDL_FreeSurface(grow_pad_surface);
        SDL_FreeSurface(grow_balls_surface); 
        SDL_FreeSurface(increase_pad_velocity_surface);  
        SDL_FreeSurface(increase_ball_velocity_surface); 
        return NULL;
  }


  SDL_Texture *grow_pad_texture = SDL_CreateTextureFromSurface(scene->render, grow_pad_surface);
  SDL_Texture *grow_balls_size_texture = SDL_CreateTextureFromSurface(scene->render, grow_balls_surface);
  SDL_Texture *increase_pad_velocity_texture = SDL_CreateTextureFromSurface(scene->render, increase_pad_velocity_surface);
  SDL_Texture *increase_ball_velocity_texture = SDL_CreateTextureFromSurface(scene->render, increase_ball_velocity_surface);

  SDL_FreeSurface(grow_pad_surface);
  SDL_FreeSurface(grow_balls_surface);
  SDL_FreeSurface(increase_pad_velocity_surface);
  SDL_FreeSurface(increase_ball_velocity_surface);



  SDL_Rect *grow_pad_rect = malloc(sizeof(SDL_Rect));
  SDL_Rect *grow_balls_size_rect = malloc(sizeof(SDL_Rect));
  SDL_Rect *pad_velocity_rect = malloc(sizeof(SDL_Rect));
  SDL_Rect *ball_velocity_rect = malloc(sizeof(SDL_Rect));
  
  assets->grow_pad->path = NULL;
  assets->grow_pad->texture = grow_pad_texture;
  assets->grow_pad->position = grow_pad_rect;


  assets->grow_balls_size->path = NULL;
  assets->grow_balls_size->texture = grow_balls_size_texture;
  assets->grow_balls_size->position = grow_balls_size_rect;

  assets->increase_pad_velocity->path = NULL;
  assets->increase_pad_velocity->texture = increase_pad_velocity_texture;
  assets->increase_pad_velocity->position = pad_velocity_rect;

  assets->increase_ball_velocity->path = NULL;
  assets->increase_ball_velocity->texture = increase_ball_velocity_texture;
  assets->increase_ball_velocity->position = ball_velocity_rect;


  return assets; 
}


void destroy_power_assets(PowerAssets *assets) {
    if (assets == NULL) return;

    if (assets->grow_pad) {
        if (assets->grow_pad->texture)
            SDL_DestroyTexture(assets->grow_pad->texture);
        if (assets->grow_pad->position)
            free(assets->grow_pad->position);
        free(assets->grow_pad);
    }

    if (assets->grow_balls_size) {
        if (assets->grow_balls_size->texture)
            SDL_DestroyTexture(assets->grow_balls_size->texture);
        if (assets->grow_balls_size->position)
            free(assets->grow_balls_size->position);
        free(assets->grow_balls_size);
    }

    if (assets->increase_pad_velocity) {
        if (assets->increase_pad_velocity->texture)
            SDL_DestroyTexture(assets->increase_pad_velocity->texture);
        if (assets->increase_pad_velocity->position)
            free(assets->increase_pad_velocity->position);
        free(assets->increase_pad_velocity);
    }

    if (assets->increase_ball_velocity) {
        if (assets->increase_ball_velocity->texture)
            SDL_DestroyTexture(assets->increase_ball_velocity->texture);
        if (assets->increase_ball_velocity->position)
            free(assets->increase_ball_velocity->position);
        free(assets->increase_ball_velocity);
    }

    free(assets);
}

