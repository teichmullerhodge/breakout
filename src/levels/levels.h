#ifndef  LEVELS_H
#define  LEVELS_H 


#include <stdlib.h> 

typedef enum {

  LEVEL_ONE,
  LEVEL_TWO,
  LEVEL_THREE,
  LEVEL_FOUR,
  FINAL_LEVEL

} Level;

size_t get_levels_bricks_quantity(Level level);


#endif

