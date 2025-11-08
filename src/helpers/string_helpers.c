#include "string_helpers.h"
#include <string.h>
#include <stdio.h>


void remove_not_allowed_chars(char *str){
  
  if(str == NULL) return;
  size_t i = 0;
  size_t j = 0;
  while(str[i] != '\0') {
  
    char c = str[i];
    if(c == '0' || c == '1') {
      str[j++] = c;
    }
    i++;
  }

  str[j] = '\0';


}




