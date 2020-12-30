#ifndef MENU_H
#define MENU_H
#include <lcom/lcf.h>


#include <lcom/lcf.h>
#include "keyboard.h"
#include "videocard.h"
#include "mouse.h"
#include "background.h"
#include "i8254.h"
#include "animate_sprite.h"

#include "xpm/logo.xpm"
#include "xpm/cursor.xpm"
#include "xpm/play_button.xpm"
#include "xpm/exit_button.xpm"

/**
 * @brief 
 * 
 */
typedef enum {MENU,GAME,EXIT} state;

/**
 * @brief 
 * 
 * @param cursor 
 * @param x 
 * @param y 
 * @param width 
 * @param height 
 * @return int 
 */
int detect_colisions(Sprite* cursor,uint16_t x,uint16_t y, uint16_t width,uint16_t height);

/**
 * @brief 
 * 
 * @param game_state 
 * @return int 
 */
int menu(state* game_state);


#endif
