#ifndef ANIMATE_SPRITE_H
#define ANIMATE_SPRITE_H

#include <stdarg.h> // va_* macros are defined here
#include "sprite.h"
#include "sphere.h"


typedef struct {
    Sprite *sp; // standard sprite
    int aspeed; // no. frames per pixmap
    int cur_aspeed; // no. frames left to next change
    int num_fig; // number of pixmaps
    int cur_fig; // current pixmap
    uint8_t** map;
}AnimSprite;


/**
 * @brief Create a animSprite object
 * 
 * @param x 
 * @param y 
 * @param no_pic 
 * @param pic1 
 * @param ... 
 * @return AnimSprite* 
 */
AnimSprite *create_animSprite(uint16_t x, uint16_t y, uint8_t no_pic, xpm_row_t pic1[], ...);

/**
 * @brief 
 * 
 * @param asp 
 * @return int 
 */
int animate_sprite(AnimSprite *asp);

/**
 * @brief 
 * 
 * @param asp 
 */
void destroy_animSprite(AnimSprite* asp);

/**
 * @brief Get the cur fig object
 * 
 * @param asp 
 * @return int 
 */
int get_cur_fig(AnimSprite* asp);
#endif
