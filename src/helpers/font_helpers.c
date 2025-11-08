#include "font_helpers.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../declarations/declarations.h"
#include "../logger/logger.h"

TextLabel * render_text(Scene* scene, TTF_Font *font, const char *message, Color color, TextLabel *self){


    if(self && self->texture && strcmp(self->text, message) == 0) {
      return self; 
    }

    if(self && self->texture) {
      SDL_DestroyTexture(self->texture);
      self->texture = NULL;
    }

    SDL_Color c = {color.r, color.g, color.b, color.a };


    SDL_Surface* surface = TTF_RenderText_Solid(font, message, c);
    if (surface == NULL) {
        char err[256];
        snprintf(err, sizeof(err), "Error creating surface: %s\n", TTF_GetError());
        LOGGER_ERROR(err);
        return NULL;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(scene->render, surface);
    if (texture == NULL) {

        char err[256];
        snprintf(err, sizeof(err), "Error creating texture: %s\n", TTF_GetError());
        LOGGER_ERROR(err);
        SDL_FreeSurface(surface);
        return NULL;
    }
    
    if (self == NULL) {
        LOGGER_DEBUG("Memory allocation for self.");
        self = malloc(sizeof(TextLabel));
        memset(self, 0, sizeof(TextLabel));

    }
    
    self->texture = texture;
    self->width = surface->w;
    self->height = surface->h;  

    snprintf(self->text, sizeof(self->text), "%s", message);
    SDL_FreeSurface(surface);
    return self;
}
