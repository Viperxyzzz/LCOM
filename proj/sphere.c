#include "sphere.h"



Sphere* create_sphere(uint16_t x, uint16_t y)
{
    
    
    Sphere* sphere = (Sphere*)malloc(sizeof(Sphere));
    sphere->x = x;
    sphere->y = y;

    //sphere->angle = ((float)rand() / (float)(RAND_MAX)) * 3.14159f * 2.0f;
    //sphere->angle = 120.0f;
    //sphere->dx = cosf(sphere->angle);
    //sphere->dy = sinf(sphere->angle);

    sphere->dx = 1;
    sphere->dy = 1;

    sphere->old_x = x;
    sphere->old_y = y;

    xpm_image_t img;
    xpm_load(ball_xpm,XPM_8_8_8,&img);

    sphere->width = img.width;
    sphere->height = img.height;
    sphere->map = img.bytes;

    sphere->diameter = 16;
    return sphere;
}

int draw_sphere(Sphere* sphere)
{

    uint32_t index = 0;
    uint8_t* map = sphere->map;

    for (uint16_t j = sphere->y ; j < sphere->y + sphere->height; j++)
    {
        for(uint16_t i = sphere->x; i < sphere->x + sphere->width; i++)
        {
            uint32_t color = 0;
            memcpy(&color,&map[index],3);

            pixel_set_color(i,j,color);
            index += 3;
        }
    }


    return 0;

}

