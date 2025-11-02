#ifndef ENTITY_H 
#define ENTITY_H 

#include "../declarations/declarations.h"
#include <SDL2/SDL.h>
#include "../scene/scene.h"
#include <stdbool.h> 
#include "../levels/levels.h"
typedef struct {

  u8 r;
  u8 g;
  u8 b;
  u8 a;

} Color;

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




#define INCREASE_PAD_SIZE_POSSIBILITY 3
#define INCREASE_PAD_SIZE_VALUE 40

#define DOUBLE_BALLS_POSSIBILITY 0


#define INCREASE_BALLS_SIZE_POSSIBILITY 5
#define INCREASE_BALLS_SIZE_WIDTH 10
#define INCREASE_BALLS_SIZE_HEIGHT 10

#define INCREASE_PAD_VELOCITY_POSSIBILITY 0
#define INCREASE_PAD_VELOCITY_VALUE 100.0f 

#define INCREASE_BALL_VELOCITY_POSSIBILITY 0
#define INCREASE_BALL_VELOCITY_VALUE 100.0f


// Limits 
#define BALL_MAX_WIDTH 180
#define BALL_MAX_HEIGHT 180

typedef enum {

  POWER_NONE,
  INCREASE_PAD_SIZE,
  DOUBLE_BALLS,
  INCREASE_BALLS_SIZE,
  INCREASE_PAD_VELOCITY,
  
  // Downgrades 
  INCREASE_BALL_VELOCITY

} PowerUps;



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

void construct_brick_levels(Brick *bricks_buffer, size_t bricks_buffer_size, Level level, size_t n_bricks);

#endif 
