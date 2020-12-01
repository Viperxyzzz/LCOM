#ifndef VIDEO_H
#define VIDEO_H

#include <lcom/lcf.h>

int (set_vbe_mod)(uint16_t mode);
void (pixel_set_color)(uint16_t x, uint16_t y, uint32_t color);
int (vg_read_xpm)(xpm_map_t xpm,uint16_t x, uint16_t y);

#endif
