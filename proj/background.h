#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <lcom/lcf.h>
#include "videocard.h"

#include "xpm/background.xpm"




void alloc_background();

void free_background();

int draw_background(bool init);

void reset_to_background();


#endif 
