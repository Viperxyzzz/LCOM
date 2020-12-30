#ifndef GAME_H
#define GAME_H

#include <lcom/lcf.h>
#include "keyboard.h"
#include "videocard.h"
#include "sphere.h"
#include "background.h"
#include "bricks.h"
#include "animate_sprite.h"
#include "i8042.h"
#include "i8254.h"



#include "xpm/paddle.xpm"



#include "xpm/heart.xpm"
#include "xpm/numbers/0.xpm"
#include "xpm/numbers/1.xpm"
#include "xpm/numbers/2.xpm"
#include "xpm/numbers/3.xpm"
#include "xpm/numbers/4.xpm"
#include "xpm/numbers/5.xpm"
#include "xpm/numbers/6.xpm"
#include "xpm/numbers/7.xpm"
#include "xpm/numbers/8.xpm"
#include "xpm/numbers/9.xpm"




#include "xpm/explosao0.xpm"
#include "xpm/explosao1.xpm"
#include "xpm/explosao2.xpm"
#include "xpm/explosao3.xpm"
#include "xpm/explosao4.xpm"
#include "xpm/explosao5.xpm"
#include "xpm/explosao6.xpm"
#include "xpm/explosao7.xpm"




int draw_score(int points,Sprite **numbers);

void game_over(uint8_t won);

//int check_brick_colisions(Sphere* sphere, Brick* brick);
//int draw_lives();


//int draw_multiplier();




/**
 * @brief 
 * 
 * @return int 
 */
int breakout();




#endif
