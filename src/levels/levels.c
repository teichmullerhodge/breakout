#include "levels.h"



size_t get_levels_bricks_quantity(Level level){

  switch(level) {
    case LEVEL_ONE: return 60;
    case LEVEL_TWO: return 60;
    case LEVEL_THREE: return 80;
    case LEVEL_FOUR: return 90;
    case FINAL_LEVEL: return 100;
  }

  return 60; // Should never reach this.

}

