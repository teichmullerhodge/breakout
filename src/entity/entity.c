#include "entity.h"
#include "../appconfig/appconstants.h"
#include "../logger/logger.h"
#include <stdio.h>
#include "../helpers/file_helpers.h" 
#include "../helpers/color_helpers.h"
#include "../appconfig/appconfig.h"

void color_entity(Entity *entity, Scene *scene, Color *color) {

  if(entity == NULL) {
      LOGGER_DEBUG("Entity is null at color_entity.");
      return;
  }

  if(scene == NULL) {
    LOGGER_DEBUG("Scene is null at color_entity");
    return;
  }

  if(scene->render == NULL){
    LOGGER_DEBUG("Scene renderer is null at color_entity");
    return;
  }

  if(color == NULL) {
    LOGGER_DEBUG("Color is null at color_entity");
    return;

  }



  SDL_SetRenderDrawColor(scene->render, color->r, color->g, color->b, color->a);
  SDL_RenderFillRect(scene->render, &entity->rect); 
  
  entity->color.r = color->r;
  entity->color.g = color->g;
  entity->color.b = color->b;
  entity->color.a = color->a;

  return;
}
  

Pad create_pad(){
  
  SDL_Rect pad_rect = {100, 100, 100, 10};
  Pad pad = {350.0f, 575.0f, BREAKOUT_PAD_VELOCITY, BREAKOUT_PAD_VELOCITY, (Color){40,100,255,60}, pad_rect, true};

  return pad;

}
Ball create_ball(){

  SDL_Rect ball_rect = {300, 300, 20, 20};
  Ball ball = {100, 500, BREAKOUT_BALL_VELOCITY, BREAKOUT_BALL_VELOCITY, (Color){255,255,255,255}, ball_rect, true};
  return ball;

}


#define MAX_N_BRICKS 2048 

void construct_brick_levels(Brick *bricks_buffer, size_t bricks_buffer_size, Level level, char *custom_path){


  if(bricks_buffer_size >= MAX_N_BRICKS){
    LOGGER_ERROR("The bricks buffer has a size greater than MAX_N_BRICKS");
    return;
  }

  SDL_Rect bricks_rectangles[MAX_N_BRICKS];

  char level_path[128];
  snprintf(level_path, sizeof(level_path), "../levels/level%d.lvl", level);

  printf("Level path: %s\n", level_path);
  char *file_contents = custom_path == NULL ? read_file_contents(level_path) : read_file_contents(custom_path);


  size_t index = 0;
  size_t row = 0;
  size_t col = 0;
  const size_t column_spacing = 50;

  printf("Size of contents: %s - %ld\n", file_contents, strlen(file_contents));

  for (size_t c = 0; c < strlen(file_contents); c++) {
        if (file_contents[c] == '\n') { 
            row++; 
            col = 0; 
            continue;
          };
         col++;
         SDL_Rect rect = { col * 67, column_spacing * row, 50, 30 };
         bricks_rectangles[index] = rect; 
         bool is_brick = file_contents[c] == '1';
         Entity entity = {rect.x, rect.y, 0.0f, 0.0f, is_brick ? random_color() : APPCONFIG_BG_COLOR, bricks_rectangles[index], true};
        
        i32 power_possibility = rand() % 100;
        bricks_buffer[index].power = POWER_NONE;
        bool power_set = false;

        if(power_possibility >= 0 && power_possibility <= PROBABILITY_GROW_PAD){
          bricks_buffer[index].power = POWER_GROW_PAD;
          power_set = true;
        }
        if(power_possibility >= 0 && power_possibility <= PROBABILITY_DOUBLE_BALLS && !power_set){
          bricks_buffer[index].power = POWER_DOUBLE_BALLS;
          power_set = true;
        }
        if(power_possibility >= 0 && power_possibility <= PROBABILITY_BALLS_SIZE && !power_set){
          bricks_buffer[index].power = POWER_GROW_BALLS_SIZE;
          power_set = true;
        }
        if(power_possibility >= 0 && power_possibility <= PROBABILITY_INCREASE_BALL_VELOCITY && !power_set){
          bricks_buffer[index].power = POWER_INCREASE_BALL_VELOCITY;
          power_set = true;
        }
        if(power_possibility >= 0 && power_possibility <= PROBABILITY_INCREASE_PAD_VELOCITY && !power_set){
          bricks_buffer[index].power = POWER_INCREASE_PAD_VELOCITY;
          power_set = true;
        }

        bricks_buffer[index].base = entity;
        bricks_buffer[index].destroyed = !is_brick; // non bricks are 'destroyed'

        index++;
      }

  printf("Number of bricks: %ld\n", index);

  /*
  size_t color_index = 0;

  static Color lines_colors[] = {
    {215, 67, 71, 255},
    {194, 93, 47, 255},
    {205, 162, 9, 255},
    {83, 179, 85, 255},
    {55, 61, 216, 255},
    {113, 60, 205, 255},
    {0, 198, 197, 255}
  };
  */

}

Pixel *new_window_pixels(size_t width, size_t height){

  size_t pixels_amount = width * height;
  Pixel *pixels = malloc(sizeof(Pixel) * (pixels_amount));

  if(pixels == NULL){
    LOGGER_ERROR("Failed to initialize pixels at entity.");
    return NULL;
  }
  size_t index = 0;
  for(size_t row = 0; row < height; row++){
    for(size_t col = 0; col < width; col++){
      pixels[index].x = col;
      pixels[index].y = row;
      pixels[index].color = (Color){0,0,0,0};
    }
  }


  return pixels;
  

}
