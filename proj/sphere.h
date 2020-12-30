#ifndef SPHERE_H
#define SPHERE_H
#include <math.h>
#include <stdio.h>
#include "videocard.h"


#include "xpm/ball.xpm"



/**
 * @brief 
 * 
 */
typedef struct 
{
    uint16_t x,y,old_x,old_y;
    int dx,dy;
    int width,height;
    int diameter;
    uint8_t* map;

}Sphere;
/**
 * @brief Create a sphere object
 * 
 * @param x 
 * @param y 
 * @param radium 
 * @param xpm
 * @return Sphere* 
 */
Sphere* create_sphere(uint16_t x, uint16_t y);

int draw_sphere(Sphere* sphere);



#endif
