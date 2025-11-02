#include "gamelogic.h"
#include "../appconfig/appconfig.h"
#include "../levels/levels.h"
#include "../logger/logger.h"

void check_pressed_flags(SDL_Event e, bool* left, bool *right) {
    if (e.type == SDL_KEYDOWN){ 
        switch (e.key.keysym.sym){
          case SDLK_LEFT: *left = true; break;
          case SDLK_RIGHT: *right = true; break;
        }
      }
      if (e.type == SDL_KEYUP){
        switch (e.key.keysym.sym){
          case SDLK_LEFT: *left = false; break;
          case SDLK_RIGHT: *right = false; break;
        }
      }
}

bool should_quit(SDL_Event e){
  return e.type == SDL_QUIT;
}

void handle_ball_window_colissions(Ball *ball) {

    if (ball->base.y <= 0) {
      ball->base.y = 0;
      ball->base.velocityY *= -1;
    }
    if (ball->base.y + ball->base.rect.h >= APPCONFIG_WINDOW_HEIGHT) {
      ball->base.y = APPCONFIG_WINDOW_HEIGHT - ball->base.rect.h;
      ball->base.velocityY *= -1;
    }
    if (ball->base.x <= 0) {
      ball->base.x = 0;
      ball->base.velocityX *= -1;
    }
    if (ball->base.x + ball->base.rect.w >= APPCONFIG_WINDOW_WIDTH) {
      ball->base.x = APPCONFIG_WINDOW_WIDTH - ball->base.rect.w;
      ball->base.velocityX *= -1;
    }

}

void handle_ball_pad_colission(Ball *ball, Pad* pad){

   
    if (SDL_HasIntersection(&pad->base.rect, &ball->base.rect)) {
      ball->base.y = pad->base.y - ball->base.rect.h;
      ball->base.rect.y = (int)ball->base.y;

      ball->base.velocityY *= -1;

      f32 pad_center = pad->base.x + pad->base.rect.w / 2.0f;
      f32 ball_center = ball->base.x + ball->base.rect.w / 2.0f;
      f32 diff = (ball_center - pad_center) / (pad->base.rect.w / 2.0f);
      ball->base.velocityX += diff * 100; 
    }
}

bool all_bricks_destroyed(Brick *bricks, size_t bricks_size) {

  for(size_t k = 0; k < bricks_size; k++){
    if(!bricks[k].destroyed) return false;
  }

  return true;

}

void should_reset_bricks(Brick *bricks, size_t bricks_size){

  if(all_bricks_destroyed(bricks, bricks_size)){
   for(size_t k = 0; k < bricks_size; k++){
    bricks[k].destroyed = false;
    }  
  }
}

void handle_bricks_draw_and_colission(Scene *scene, Ball *ball, Pad *pad, Brick *bricks, size_t bricks_size){

    for(size_t k = 0; k < bricks_size; k++) {
           if(bricks[k].destroyed) continue;

      SDL_RenderDrawRect(scene->render, &bricks[k].base.rect);
      color_entity(&bricks[k].base, scene, &bricks[k].base.color);
      SDL_Rect collision_rect;

      if(SDL_IntersectRect(&bricks[k].base.rect, &ball->base.rect, &collision_rect)){
         
          bricks[k].destroyed = true;
          if(collision_rect.w < collision_rect.h) {
            ball->base.velocityX *= -1;
            continue;
          }
          
          ball->base.velocityY *= -1;
          if(bricks[k].power != POWER_NONE) {
            LOGGER_DEBUG("Found a power!");
            PowerUps power = bricks[k].power;
            if(power == INCREASE_PAD_SIZE) pad->base.rect.w += INCREASE_PAD_SIZE_VALUE;
            if(power == DOUBLE_BALLS) { 
              LOGGER_WARNING("Power not implemented.");
              (void)power; // TODO
            }
            if(power == INCREASE_BALLS_SIZE && ball->base.rect.w <= BALL_MAX_WIDTH && ball->base.rect.h <= BALL_MAX_HEIGHT) {
              ball->base.rect.w += INCREASE_BALLS_SIZE_WIDTH;
              ball->base.rect.h += INCREASE_BALLS_SIZE_HEIGHT;
            }

            if(power == INCREASE_PAD_VELOCITY && pad->base.velocityX <= 999.0f) {
              LOGGER_WARNING("Power not implemented.");
              (void)power; // TODO
             
            } 
            if(power == INCREASE_BALL_VELOCITY && ball->base.velocityX <= 999.0f) {
              LOGGER_WARNING("Power not implemented.");
              (void)power; // TODO
            } 

          }
      } 
    }
}

void update_ball_position(Ball *ball, f32 delta_time){

    ball->base.x += ball->base.velocityX * delta_time;
    ball->base.y += ball->base.velocityY * delta_time;


    ball->base.rect.x = (int)ball->base.x;
    ball->base.rect.y = (int)ball->base.y;



}

void update_pad_position(SDL_Window *win, Pad *pad, bool left_pressed, bool right_pressed, f32 delta_time){

    i32 win_width;
    i32 win_height;

    SDL_GetWindowSize(win, &win_width, &win_height);

    if (left_pressed && pad->base.x >= 0)  pad->base.x -= pad->base.velocityX * delta_time;
    if (right_pressed && pad->base.x <= (win_width - 100)) pad->base.x += pad->base.velocityX * delta_time;

    pad->base.rect.x = (int)pad->base.x;
    pad->base.rect.y = (int)pad->base.y;

}



void run_game(SDL_Window *win, Scene* scene, Pad* pad, Ball* ball, Brick* bricks){

  u64 now = SDL_GetPerformanceCounter();
  u64 last = 0;
  f64 delta_time = 0;
  bool running = true;
  bool left_pressed = false, right_pressed = false;
  SDL_Event e;

  size_t number_bricks = get_levels_bricks_quantity(LEVEL_ONE);

  while(running) {
 
    last = now;
    now = SDL_GetPerformanceCounter();
    delta_time = (f64)(now - last) / SDL_GetPerformanceFrequency();
  
    while (SDL_PollEvent(&e)){
      if(should_quit(e)) running = false;
      check_pressed_flags(e, &left_pressed, &right_pressed); 
    }

    update_pad_position(win, pad, left_pressed, right_pressed, delta_time);
    handle_ball_window_colissions(ball);
    handle_ball_pad_colission(ball, pad);
    handle_bricks_draw_and_colission(scene, ball, pad, bricks, number_bricks); 
    update_ball_position(ball, delta_time);
    should_reset_bricks(bricks, number_bricks);


    SDL_RenderDrawRect(scene->render, &pad->base.rect);
    color_entity(&pad->base, scene, &pad->base.color);

    SDL_RenderDrawRect(scene->render, &ball->base.rect);
    color_entity(&ball->base, scene, &ball->base.color);
  

    SDL_SetRenderDrawColor(scene->render, 13, 25, 32, 255);
    SDL_RenderPresent(scene->render);
    SDL_RenderClear(scene->render); 
  }
}

