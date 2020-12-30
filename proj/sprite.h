#ifndef SPRITE_H
#define SPRITE_H
#include <lcom/lcf.h>
#include "videocard.h"


typedef struct {
    uint16_t x, y; // current position
    uint16_t width, height; // dimensions
    uint16_t xspeed, yspeed; // current speed
    uint8_t *map; // the pixmap
} Sprite;

/**
 * @brief Create a sprite object
 * 
 * @param pic 
 * @param x 
 * @param y 
 * @param xspeed 
 * @param yspeed 
 * @return Sprite* 
 */
Sprite* create_sprite(xpm_row_t pic[],uint16_t x,uint16_t y,uint16_t xspeed,uint16_t yspeed);

/**
 * @brief 
 * 
 * @param sp 
 * @return int 
 */
int draw_sprite(Sprite* sp);

/**
 * @brief 
 * 
 * @param sp 
 */
void destroy_sprite(Sprite* sp);
#endif
