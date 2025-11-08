#include "gamelogic.h"
#include "../appconfig/appconfig.h"
#include "../levels/levels.h"
#include "../logger/logger.h"

void check_pressed_flags(SDL_Event e, GameKeys* keys) {
    if (e.type == SDL_KEYDOWN){ 
        switch (e.key.keysym.sym){
          case SDLK_ESCAPE: keys->esc_pressed = true; break; 
          case SDLK_LEFT: keys->left_pressed = true; break;
          case SDLK_RIGHT: keys->right_pressed = true; break;
          case SDLK_p: keys->p_pressed = !keys->p_pressed; break;
          case SDLK_r: keys->r_pressed = true; break;
        }
      }
      if (e.type == SDL_KEYUP){
        switch (e.key.keysym.sym){
          case SDLK_LEFT: keys->left_pressed = false; break;
          case SDLK_RIGHT: keys->right_pressed = false; break;
          case SDLK_r: keys->r_pressed = false; break; 
        }
      }
}

bool should_quit(SDL_Event e){
  return e.type == SDL_QUIT;
}


void handle_power_up(Scene *scene, PowerUps power, GameContext *context){
  
  
      (void)scene;

      if(power == POWER_GROW_PAD  && context->pad->base.rect.w <= LIMIT_PAD_WIDTH) context->pad->base.rect.w += VALUE_GROW_PAD;
      if(power == POWER_DOUBLE_BALLS) { 
          (void)power; // TODO
      }
      if(power == POWER_GROW_BALLS_SIZE && context->ball->base.rect.w <= LIMIT_BALL_MAX_WIDTH && context->ball->base.rect.h <= LIMIT_BALL_MAX_HEIGHT){
          context->ball->base.rect.w += VALUE_GROW_BALLS_SIZE;
          context->ball->base.rect.h += VALUE_GROW_BALLS_SIZE;


      }
      if(power == POWER_INCREASE_PAD_VELOCITY && context->pad->base.velocityX <= LIMIT_PAD_VELOCITY) {
          (void)power; // TODO
      } 
      if(power == POWER_INCREASE_BALL_VELOCITY && context->ball->base.velocityX <= LIMIT_MAX_BALL_VELOCITY) {
          (void)power; // TODO
      } 

  }




void handle_ball_window_colissions(GameContext *context) {

    if (context->ball->base.y <= 0) {

      context->ball->base.y = 0;
      context->ball->base.velocityY *= -1;
    }
    if (context->ball->base.y + context->ball->base.rect.h >= APPCONFIG_WINDOW_HEIGHT) {
        context->ball->base.y = APPCONFIG_WINDOW_HEIGHT - context->ball->base.rect.h;
        context->ball->base.velocityY *= -1;
        if(context->player->lives == 0){
        // game over 
        return;
        }
        context->player->lives--;
    }
    if (context->ball->base.x <= 0) {
      context->ball->base.x = 0;
      context->ball->base.velocityX *= -1;
    }
    if (context->ball->base.x + context->ball->base.rect.w >= APPCONFIG_WINDOW_WIDTH) {
      context->ball->base.x = APPCONFIG_WINDOW_WIDTH - context->ball->base.rect.w;
      context->ball->base.velocityX *= -1;
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

  char message[256];
  size_t destroyed = 0;
  for(size_t k = 0; k < bricks_size; k++){
    if(!bricks[k].destroyed) {
      snprintf(message, sizeof(message), "Number of bricks: %ld - destroyed: %ld", bricks_size, destroyed);
      LOGGER_DEBUG(message);
      return false;
    }
    destroyed++;
  }

  return true;

}

void should_advance_levels(GameContext *context){

  char message[256];
  snprintf(message, sizeof(message), "Bricks size: %d - destroyed: %ld", context->level_info.destructiveBricks, context->bricks_destroyed);
  LOGGER_DEBUG(message);
  if(context->bricks_destroyed == context->level_info.destructiveBricks){

    LOGGER_SUCCESS("At all_bricks_destroyed!\n");
    context->current_level++;
    context->level_info = get_level_information(context->current_level);


    
    construct_brick_levels(context->bricks, context->level_info.amountOfBricks, context->current_level);

    context->bricks_destroyed = 0;
  }
    
}

void handle_bricks_draw_and_colission(Scene *scene, GameContext *context){

    for(size_t k = 0; k < context->level_info.amountOfBricks; k++) {
      
      if(context->bricks[k].destroyed) continue;
      SDL_RenderDrawRect(scene->render, &context->bricks[k].base.rect);
      color_entity(&context->bricks[k].base, scene, &context->bricks[k].base.color);
      SDL_Rect collision_rect;

      if(!context->bricks[k].destroyed && SDL_IntersectRect(&context->bricks[k].base.rect, &context->ball->base.rect, &collision_rect)){
        
          context->player->current_score += 100;
          context->bricks[k].destroyed = true;
          context->bricks_destroyed++;
          if(context->bricks[k].power != POWER_NONE) {
            handle_power_up(scene, context->bricks[k].power, context);     
          } 

          if(collision_rect.w < collision_rect.h) {
            context->ball->base.velocityX *= -1;
            continue;
          }
          
          context->ball->base.velocityY *= -1;
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

void display_centralized_message(Scene *scene, GameContext *context, const char *message) {
    char message_buff[512];
    snprintf(message_buff, sizeof(message_buff), "%s", message);
    context->player_menu = render_text(scene, 
                                       context->font, 
                                       message_buff, 
                                       (Color){255, 255, 255, 255}, 
                                       context->player_menu);

    if (context->player_menu && context->player_menu->texture) {
      SDL_Rect dest;
      dest.w = context->player_menu->width;
      dest.h = context->player_menu->height;
      dest.x = (APPCONFIG_WINDOW_WIDTH  - dest.w) / 2;
      dest.y = (APPCONFIG_WINDOW_HEIGHT - dest.h) / 2;

      SDL_RenderCopy(scene->render, context->player_menu->texture, NULL, &dest);
    }


    SDL_SetRenderDrawColor(scene->render, 13, 25, 32, 255);
    SDL_RenderPresent(scene->render);
 }


void run_game(SDL_Window *win, Scene* scene, GameContext *context){

  u64 now = SDL_GetPerformanceCounter();
  u64 last = 0;
  f64 delta_time = 0;
  bool running = true;
 
  GameKeys keys = { 0 };
  SDL_Event e;

  bool game_over = false;
  while(running) {
    
    last = now;
    now = SDL_GetPerformanceCounter();
    delta_time = (f64)(now - last) / SDL_GetPerformanceFrequency();
  
    game_over = context->player->lives == 0;


    while (SDL_PollEvent(&e)){
      if(should_quit(e) || keys.esc_pressed) running = false;
      check_pressed_flags(e, &keys); 
    }
    if(keys.p_pressed && !game_over){
      display_centralized_message(scene, context, "Paused");
      continue;
    }

    if(game_over){

      if(keys.r_pressed) context->player->lives = 3;
      display_centralized_message(scene, context, "Game Over");
      continue;
    }

    should_advance_levels(context);
    update_pad_position(win, context->pad, keys.left_pressed, keys.right_pressed, delta_time);
    handle_ball_window_colissions(context);
    handle_ball_pad_colission(context->ball, context->pad);
    handle_bricks_draw_and_colission(scene, context); 
    update_ball_position(context->ball, delta_time);


    SDL_RenderDrawRect(scene->render, &context->pad->base.rect);
    color_entity(&context->pad->base, scene, &context->pad->base.color);

    SDL_RenderDrawRect(scene->render, &context->ball->base.rect);
    color_entity(&context->ball->base, scene, &context->ball->base.color);


    char menu_message[256];
    snprintf(menu_message, sizeof(menu_message), "S: %ld L: %d", context->player->current_score, context->player->lives);
    context->player_menu = render_text(scene, context->font, menu_message, (Color){255, 255, 255, 255}, context->player_menu);


    if(context->player_menu && context->player_menu->texture) {
       SDL_Rect dest = {20, 20, context->player_menu->width, context->player_menu->height};
       SDL_RenderCopy(scene->render, context->player_menu->texture, NULL, &dest);
    }

    SDL_SetRenderDrawColor(scene->render, 13, 25, 32, 255);
    SDL_RenderPresent(scene->render);
    SDL_RenderClear(scene->render);
  }
}

