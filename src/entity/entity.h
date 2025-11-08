#ifndef ENTITY_H 
#define ENTITY_H 

#include "../declarations/declarations.h"
#include <SDL2/SDL.h>
#include "../scene/scene.h"
#include <stdbool.h> 
#include "../levels/levels.h"
#include "../power/power.h" 

typedef struct {

  u8 r;
  u8 g;
  u8 b;
  u8 a;

} Color;


typedef struct {


  Color color;
  u32 x; 
  u32 y;


} Pixel;



typedef struct {


  f32 x, y;
  f32 velocityX, velocityY;
  Color color;
  SDL_Rect rect;
  bool active;

} Entity;


typedef struct {

  Entity base;

} Pad;

typedef struct {

  Entity base; 

} Ball; 


typedef struct {

  Entity base;
  bool destroyed; 
  PowerUps power;
} Brick; 



typedef struct {

  char name[128];
  u8 lives;
  u64 current_score;
  u64 highest_score;

} Player; 


void color_entity(Entity *entity, Scene *scene, Color *color);

Pad create_pad();
Ball create_ball();

void construct_brick_levels(Brick *bricks_buffer, size_t bricks_buffer_size, Level level, char *custom_path);


Pixel *new_window_pixels(size_t width, size_t height);


#endif 
