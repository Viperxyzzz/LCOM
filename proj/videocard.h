#ifndef VIDEO_H
#define VIDEO_H
#include <lcom/lcf.h>



#define INDEXED 0x105
#define IGNORED 0xFF00F0


extern vbe_mode_info_t vmi_p;
extern char* video_buff;

int (set_vbe_mod)(uint16_t mode);
void (pixel_set_color)(uint16_t x, uint16_t y, uint32_t color);
void (double_buff)();
void (vg_clear_screen)();
int (vg_read_xpm)(xpm_map_t xpm,uint16_t x, uint16_t y);
char* (get_videobuff)();

#endif
