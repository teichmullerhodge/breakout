#include "level_editor.h"
#include "../appconfig/appconfig.h"
#include "../logger/logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include "../helpers/color_helpers.h"



void level_editor_mode(SDL_Window *win, Scene *scene, GameContext *context){

  (void)context;
  (void)win;
  SDL_Event e;
  bool running = true;


  LevelEntities *level_entities = malloc(sizeof(LevelEntities));
  level_entities->areas = malloc(sizeof(LevelArea) * 999);


  for(size_t k = 0; k < 999; k++){
    level_entities->areas[k].should_render = false;  
  }

  size_t index = 0;

  while(running) {
    
    while(SDL_PollEvent(&e)) {
 
      if(e.type == SDL_QUIT) running = false;

      if(e.type == SDL_MOUSEBUTTONDOWN) {

        int mouseX = e.button.x;
        int mouseY = e.button.y;

        SDL_Rect rect = {
          .x = mouseX,
          .y = mouseY,
          .w = 50,
          .h = 20
        };

        level_entities->areas[index].should_render = true;
        level_entities->areas[index].rect = rect;
        index++;


        }
    
      }
  
      for(size_t k = 0; k < 99; k++){
     
        if(!level_entities->areas[k].should_render) continue;        


 
        SDL_SetRenderDrawColor(scene->render, 255, 0, 0, 255);
        SDL_RenderDrawRect(scene->render, &level_entities->areas[k].rect);
        SDL_RenderFillRect(scene->render, &level_entities->areas[k].rect); 
       
      }
 
  


      SDL_RenderPresent(scene->render);
  }
  
}



