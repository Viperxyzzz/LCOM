#ifndef BRICKS_H
#define BRICKS_H
#include <lcom/lcf.h>
#include "videocard.h"


#include "xpm/brick.xpm"




/**
 * @brief 
 * 
 */
typedef struct
{
    uint16_t x,y;
    float width, height;
    bool is_destroyed;
    uint8_t* map;
    xpm_image_t img;
}Brick;

/**
 * @brief Create a Brick object
 * 
 * @param x horizontal position of the brick
 * @param y vertical position of the brick
 * @param width the width of the brick
 * @param height the height of the brick
 * @param color the desired color for the brick
 * @return Brick* returns a brick object
 */
Brick* create_brick(uint16_t x,uint16_t y);


int draw_brick(Brick* brick);

#endif
