#include "entity.h"

#include "../logger/logger.h"


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
  Pad pad = {350.0f, 575.0f, 350.0f, 350.0f, (Color){40,100,255,60}, pad_rect, true};

  return pad;

}
Ball create_ball(){

  SDL_Rect ball_rect = {300, 300, 20, 20};
  Ball ball = {100, 500, 400.0f, 400.0f, (Color){255,255,255,255}, ball_rect, true};
  return ball;

}


#define MAX_N_BRICKS 255 

void construct_brick_levels(Brick *bricks_buffer, size_t bricks_buffer_size, Level level, size_t n_bricks){

  (void)level;

  printf("Bricks buffer size: %lu.\n", bricks_buffer_size);

  if(bricks_buffer_size >= MAX_N_BRICKS){
    LOGGER_ERROR("The bricks buffer has a size greater than MAX_N_BRICKS");
    return;
  }

  SDL_Rect bricks_rectangles[MAX_N_BRICKS];
  size_t line = 100;
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

  for (size_t k = 0; k < n_bricks; k++) {
    if (k % 10 == 0) { 
      line += 30;
      color_index++;
    }
    SDL_Rect rect = {
        .x = 100 + (k % 10) * 60,
        .y = line,
        .w = 50,
        .h = 20
    };
    bricks_rectangles[k] = rect;

    Entity entity = {rect.x, rect.y, 0.0f, 0.0f, lines_colors[color_index], bricks_rectangles[k], true};
   
    i32 power_possibility = rand() % 100;
    bricks_buffer[k].power = POWER_NONE;
    bool power_set = false;

    if(power_possibility >= 0 && power_possibility <= PROBABILITY_GROW_PAD){
      bricks_buffer[k].power = POWER_GROW_PAD;
      power_set = true;
    }
    if(power_possibility >= 0 && power_possibility <= PROBABILITY_DOUBLE_BALLS && !power_set){
      bricks_buffer[k].power = POWER_DOUBLE_BALLS;
      power_set = true;
    }
    if(power_possibility >= 0 && power_possibility <= PROBABILITY_BALLS_SIZE && !power_set){
      bricks_buffer[k].power = POWER_GROW_BALLS_SIZE;
      power_set = true;
    }
    if(power_possibility >= 0 && power_possibility <= PROBABILITY_INCREASE_BALL_VELOCITY && !power_set){
      bricks_buffer[k].power = POWER_INCREASE_BALL_VELOCITY;
      power_set = true;
    }
    if(power_possibility >= 0 && power_possibility <= PROBABILITY_INCREASE_PAD_VELOCITY && !power_set){
      bricks_buffer[k].power = POWER_INCREASE_PAD_VELOCITY;
      power_set = true;
    }



    bricks_buffer[k].base = entity;
    bricks_buffer[k].destroyed = false;
  }





}

