#ifndef  LEVELS_H
#define  LEVELS_H 


#include <stdlib.h> 
#include "../declarations/declarations.h"
typedef enum {

  LEVEL_HOLE_MIDDLE,
  LEVEL_INVERTED_PIRAMID,
  LEVEL_CHESS,
  LEVEL_GATE,
  LEVEL_MOLD_CENTER,
  LEVEL_PIRAMID,
  LEVEL_THREE_BLOCKS


} Level;

typedef struct {


  Level level;
  u32 destructiveBricks; 
  u32 amountOfBricks;

} LevelMetadata;

LevelMetadata get_level_information(Level level);


#endif

