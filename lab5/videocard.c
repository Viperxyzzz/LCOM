#include "videocard.h"

static char *video_mem;		/* Process (virtual) address to which VRAM is mapped */
static unsigned h_res;	        /* Horizontal resolution in pixels */
static unsigned v_res;	        /* Vertical resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */



//TO DO
//pass this magic numbers to macros k thx
int (set_vbe_mod)(uint16_t mode)
{
    reg86_t r;
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
    vbe_mode_info_t vmi_p;
    if(vbe_get_mode_info(mode,&vmi_p))
        return NULL;
    

    h_res = vmi_p.XResolution;
    v_res = vmi_p.YResolution;
    bits_per_pixel = vmi_p.BitsPerPixel;


    struct minix_mem_range mr;
    unsigned int vram_base;
    unsigned int vram_size;

    int r;

    /* Use VBE function 0x01 to initialize vram_base and vram_size */

    mr.mr_base = (phys_bytes)vram_base;
    mr.mr_limit = mr.mr_base + vram_size;

    if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    video_mem = vm_map_phys(SELF,(void*)mr.mr_base, vram_size);

    if(video_mem == MAP_FAILED)
        panic("couldn't map video memory");

    if(set_vbe_mode(mode))
        return NULL;
    return video_mem;
    
}
