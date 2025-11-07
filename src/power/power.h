#ifndef POWER_H 
#define POWER_H 

#include "../scene/scene.h"
#include "../models/models.h"

typedef enum {

  POWER_NONE,
  POWER_GROW_PAD,
  POWER_GROW_BALLS_SIZE,
  POWER_INCREASE_PAD_VELOCITY,
  POWER_DOUBLE_BALLS,
  POWER_INCREASE_BALL_VELOCITY

} PowerUps;

typedef enum {

  VALUE_GROW_PAD = 20,
  VALUE_GROW_BALLS_SIZE = 15,
  VALUE_INCREASE_PAD_VELOCITY = 30,
  VALUE_INCREASE_BALL_VELOCITY = 25


} PowerUpValues;


typedef enum {

  PROBABILITY_GROW_PAD = 7,
  PROBABILITY_BALLS_SIZE = 80,
  PROBABILITY_INCREASE_PAD_VELOCITY = 11,
  PROBABILITY_DOUBLE_BALLS = 4,
  PROBABILITY_INCREASE_BALL_VELOCITY = 2

} PowerUpProbability;

typedef enum {

  LIMIT_PAD_WIDTH = 999,
  LIMIT_BALL_MAX_WIDTH = 180,
  LIMIT_BALL_MAX_HEIGHT = 180,
  LIMIT_PAD_VELOCITY = 999,
  LIMIT_MAX_BALLS_IN_SCENE = 6,
  LIMIT_MAX_BALL_VELOCITY = 500

} PowerUpLimits;


typedef struct {

  Asset *grow_pad;
  Asset *grow_balls_size;
  Asset *increase_pad_velocity; 
  Asset *increase_ball_velocity;

} PowerAssets;


PowerAssets *load_power_assets(Scene *scene);


#endif 
