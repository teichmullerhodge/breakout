#include "color_helpers.h"
Color random_color() {

  Color c;
  c.r = rand() % 255;
  c.g = rand() % 255;
  c.b = rand() % 255;
  c.a = rand() % 255;
  return c;

}


