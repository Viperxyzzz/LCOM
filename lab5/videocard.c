#include "videocard.h"

static char *video_mem = NULL;		/* Process (virtual) address to which VRAM is mapped */
static unsigned h_res;	        /* Horizontal resolution in pixels */
static unsigned v_res;	        /* Vertical resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */
static vbe_mode_info_t vmi_p;


//TO DO
//pass this magic numbers to macros k thx
int (set_vbe_mod)(uint16_t mode)
{
    reg86_t r;
    memset(&r, 0, sizeof(reg86_t));
    r.ax = 0x4F02;
    r.ah = 0x4F;
    r.bx = 1 << 14 | mode;
    r.intno = 0x10;
    if(sys_int86(&r))
    {
        printf("Failed big time");
        return 1;
    }

    //TODO Specify the errors
    if(r.al != 0x4F || r.ah !=  0x00)
    {
        printf("Failed....");
        return 1;   
    }


    return 0;
}

void* (vg_init)(uint16_t mode)
{
    if(vbe_get_mode_info(mode,&vmi_p))
        return NULL;
    

    h_res = vmi_p.XResolution;
    v_res = vmi_p.YResolution;
    bits_per_pixel = vmi_p.BitsPerPixel;


    struct minix_mem_range mr;
    unsigned int vram_base = vmi_p.PhysBasePtr;
    unsigned int vram_size = h_res * v_res * (bits_per_pixel >> 3);

    int r;

    /* Use VBE function 0x01 to initialize vram_base and vram_size */

    mr.mr_base = (phys_bytes)vram_base;
    mr.mr_limit = mr.mr_base + vram_size;

    if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    video_mem = vm_map_phys(SELF,(void*)mr.mr_base, vram_size);

    if(video_mem == MAP_FAILED)
        panic("couldn't map video memory");

    if(set_vbe_mod(mode))
        return NULL;
    return video_mem;
    
}


void (pixel_set_color)(uint16_t x, uint16_t y, uint32_t color)
{
    char* base = video_mem + (bits_per_pixel >> 3) * (y * h_res + x);
    for(uint8_t j = 0; j < (bits_per_pixel >> 3); j++)
    {
        *base = color >> (j * 8);
        base++;
    }
}


int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color)
{ 
    char* base = video_mem + (bits_per_pixel >> 3) * (y * h_res + x);
    for(uint16_t i = 0; i < len; i++)
    {
        for (uint8_t j = 0; j < (bits_per_pixel >> 3) ; j++)
        {
            *base = color >> (j * 8);
            base++;
        }
    }
    return 0;
}



int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color)
{
    for(uint16_t i = y; i < y + height; i++)
    {
        vg_draw_hline(x,i,width,color);
    }
    return 0;
}


int (vg_read_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y)
{
    xpm_image_t img;
    uint8_t* map = xpm_load(xpm,XPM_INDEXED,&img);
    uint16_t index = 0;
    
    
    for (uint16_t j = y ; j < y + img.height; j++)
    {
        for(uint16_t i = x; i < x + img.width; i++)
        {
            pixel_set_color(i,j,map[index]);
            index++;
        }
    }


    return 0;
}
//END THIS (PROB NOT USING FOR PROJECT THO :3)
/*
int vg_draw_rectangles(uint16_t mode,uint8_t no_rectangles,uint32_t first,uint8_t step)
{
    unsigned x_size = h_res / no_rectangles;
    unsigned y_size = h_res / no_rectangles;

    for (unsigned i = 0; i < x_size; i++)
    {
        for(unsigned j = 0; j < y_size; j++)
        {
            if(mode == INDEXED)
            {
                uint32_t color = (first + (i * no_rectangles + j) * step) % (1 << bits_per_pixel);
                vg_draw_rectangle(i * x_size,j * y_size,x_size,y_size,color);
            }
            //FIX THIS CRINGE ELSE K THX 
            //FIX THIS CRINGE ELSE K THX 
            //FIX THIS CRINGE ELSE K THX 
            //FIX THIS CRINGE ELSE K THX 
            //FIX THIS CRINGE ELSE K THX 
            else
            {
                //Idfk
            }
        }
    }





    return 0;
}*/

