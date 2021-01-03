#ifndef MENU_H
#define MENU_H
#include <lcom/lcf.h>


#include <lcom/lcf.h>
#include "keyboard.h"
#include "videocard.h"
#include "mouse.h"
#include "rtc.h"
#include "background.h"
#include "i8254.h"
#include "animate_sprite.h"

#include "../assets/logo.xpm"
#include "../assets/cursor.xpm"
#include "../assets/play_button.xpm"
#include "../assets/exit_button.xpm"

/**
 * @brief enum with all the possible game states
 * 
 */
typedef enum {MENU,GAME,EXIT} state;

/**
 * @brief detects the colisions between the cursor and the other entities of the menu
 * 
 * @param cursor the cursor we're checking
 * @param x horizontal position of the entity 
 * @param y vertical position of the entity
 * @param width width of the entity
 * @param height height of the entity
 * @return int 0 in case it goes sucessfully, 1 otherwise
 */
 
int detect_colisions(Sprite* cursor,uint16_t x,uint16_t y, uint16_t width,uint16_t height);

/**
 * @brief main menu loop
 * 
 * @param game_state the state we're currently on. Will be changed during the execution of the menu
 * @return int 0 in case it goes sucessfully, 1 otherwise
 */
int menu(state* game_state);


#endif
