#include "menu.h"


int detect_colisions(Sprite* cursor,uint16_t x,uint16_t y, uint16_t width,uint16_t height)
{
    if(cursor->x < x || cursor->x > x + width)
        return 0;
    if(cursor->y < y || cursor->y > y + height)
        return 0;
    return 1;
}


int menu(state* game_state)
{
    //----------------
    uint8_t timer_bit_no = TIMER0_IRQ;
    int     timer_bit_mask = BIT(TIMER0_IRQ);
    if(timer_subscribe_int(&timer_bit_no))
        return 1;
    int     mouse_bit_mask = BIT(12);
    if(send_cmd_mouse(ENABLE_DATA))
        return 1;
    if(mouse_subscribe_int())
        return 1;
    //----------------

    Sprite *cursor = create_sprite(cursor_xpm,400,300,0,0);
    Sprite *logo = create_sprite(logo_xpm,200,100,0,0);
    Sprite *play = create_sprite(play_xpm,300,230,0,0);
    Sprite *hovering_play = create_sprite(hovering_play_xpm,300,230,0,0);
    Sprite *exit = create_sprite(exit_xpm,300,320,0,0);
    Sprite *hovering_exit = create_sprite(hovering_exit_xpm,300,230,0,0);



    //save of the original xpm
    uint8_t* play_map = play->map;
    uint8_t* exit_map = exit->map;



    uint8_t choosen = 0;
    bool init = true;
    alloc_background();
    
    
    int ipc_status,r;
    message msg;


    
    while (!choosen) {
        // Get a request message
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
        printf("driver_receive failed with: %d", r);
        continue;
        }
        if (is_ipc_notify(ipc_status)) { // received notification
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: // hardware interrupt notification
            if (msg.m_notify.interrupts & timer_bit_mask) {
                if(init)
                {
                    draw_background(true);
                    init = false;
                }
                reset_to_background();
                draw_sprite(play);
                draw_sprite(exit);
                draw_sprite(logo);
                draw_sprite(cursor);
                double_buff();
            }
            if (msg.m_notify.interrupts & mouse_bit_mask)
            {
                if(analize_buffer())
                    return 1;
                if(process_packet())
                    return 1;
                if(complete)
                {
                    parse_packet();
                    if(!(cursor->x + mouse_packets.delta_x <= 0))
                        cursor->x += mouse_packets.delta_x;
                    if(!(cursor->y + mouse_packets.delta_y <= 0))
                        cursor->y -= mouse_packets.delta_y;
                    if(cursor->x + cursor->width >= vmi_p.XResolution)
                        cursor->x = vmi_p.XResolution - cursor->width;
                    if(cursor->y + cursor->height >= vmi_p.YResolution)
                        cursor->y = vmi_p.YResolution - cursor->height;
                    if(detect_colisions(cursor,play->x,play->y,play->width,play->height))
                    {
                        play->map = hovering_play->map;    
                        if(mouse_packets.lb)
                        {
                            choosen = 1;
                            (*game_state) = GAME;
                        }
                    }
                    else if(detect_colisions(cursor,exit->x,exit->y,exit->width,exit->height))
                    {
                        exit->map = hovering_exit->map;
                        if(mouse_packets.lb)
                        {
                            choosen = 1;
                            (*game_state) = EXIT;
                        }
                    }
                    else
                    {
                        play->map = play_map;
                        exit->map = exit_map;                    
                    }
                }
            }
            break;

            default:
            break; // no other notifications expected: do nothing
        }
        }
        else { //received a standard message, not a notification
        // no standard messages expected: do nothing
        }
    }
    if (timer_unsubscribe_int())
        return 1;
    if (mouse_unsubscribe_int())
        return 1;
    if(send_cmd_mouse(DISABLE_DATA))
        return 1;
    return 0;
}
