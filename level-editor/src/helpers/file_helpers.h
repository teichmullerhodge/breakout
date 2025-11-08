#ifndef FILE_HELPERS_H
#define FILE_HELPERS_H 


#include <stdbool.h>

char *read_file_contents(const char *path);

bool save_file_contents(const char *path, char *contents);



#endif 
