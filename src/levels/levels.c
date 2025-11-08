#include "levels.h"
#include "../helpers/file_helpers.h"
#include <stdio.h>
#include <string.h>

LevelMetadata get_level_information(Level level){

  LevelMetadata meta = { level, 0, 0 };


  char level_path[128];
  snprintf(level_path, sizeof(level_path), "../levels/level%d.lvl", level);
  char *file_contents = read_file_contents(level_path);
  u32 destructive_bricks = 0;
  u32 amount_of_bricks = 0;
  for(size_t k = 0; k < strlen(file_contents); k++){
    if(file_contents[k] == '\n') continue;
    if(file_contents[k] == '1') destructive_bricks++;    
    amount_of_bricks++;
  
  }

  meta.amountOfBricks = amount_of_bricks;
  meta.destructiveBricks = destructive_bricks;
  return meta;

  
}

