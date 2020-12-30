#include "game.h"


//2 numeros maximo
int draw_score(int points,Sprite **numbers)
{
    //spaghetti :D
    int points_save = points;
    uint8_t size = 0;
    while(points_save)
    {
        size++;
        points_save /= 10;
    }

    int score[2];
    
    points_save = points;

    for(int i = 0; i < 2; i++)
    {
        if(i > size)
            score[i] = 0;
        else
        {
            score[i] = points_save % 10;
            points_save /= 10;
        } 
    }

    for(int i = 0; i < 2; i++)
    {
        switch(score[i])
        {
            case 0:
                numbers[0]->x = 400 - 64 * i;
                draw_sprite(numbers[0]);
                break;
            case 1:
                numbers[1]->x = 400 - 64 * i;
                draw_sprite(numbers[1]);
                break;
            case 2:
                numbers[2]->x = 400 - 64 * i;
                draw_sprite(numbers[2]);
                break;
            case 3:
                numbers[3]->x = 400 - 64 * i;
                draw_sprite(numbers[3]);
                break;
            case 4:
                numbers[4]->x = 400 - 64 * i;
                draw_sprite(numbers[4]);
                break;
            case 5:
                numbers[5]->x = 400 - 64 * i;
                draw_sprite(numbers[5]);
                break;
            case 6:
                numbers[6]->x = 400 - 64 * i;
                draw_sprite(numbers[6]);
                break;
            case 7:
                numbers[7]->x = 400 - 64 * i;
                draw_sprite(numbers[7]);
                break;
            case 8:
                numbers[8]->x = 400 - 64 * i;
                draw_sprite(numbers[8]);
                break;
            case 9:
                numbers[9]->x = 400 - 64 * i;
                draw_sprite(numbers[9]);
                break;
            default:
                return 1;    
        }
    }

    return 0;
}

void game_over(uint8_t won)
{
    reset_to_background();
    
    
    
    double_buff();

    
}

int breakout()
{
    //interrupts stuff
    uint8_t keyboard_bit_no = IRQ1;
    int     keyboard_bit_mask = BIT(IRQ1);
    if (kbd_subscribe_int(&keyboard_bit_no))
        return 1;

    uint8_t timer_bit_no = TIMER0_IRQ;
    int     timer_bit_mask = BIT(TIMER0_IRQ);
    if(timer_subscribe_int(&timer_bit_no))
        return 1;
    

    timer_set_frequency(0,60);

    //---------------------------------------

    //initializing game stuff
    uint8_t lives = 3;
    uint16_t score = 0;
    bool init = true;


    Sprite* numbers[10];
    numbers[0] = create_sprite(zero_xpm,400,10,0,0);
    numbers[1] = create_sprite(one_xpm,400,10,0,0);
    numbers[2] = create_sprite(two_xpm,400,10,0,0);
    numbers[3] = create_sprite(three_xpm,400,10,0,0);
    numbers[4] = create_sprite(four_xpm,400,10,0,0);
    numbers[5] = create_sprite(five_xpm,400,10,0,0);
    numbers[6] = create_sprite(six_xpm,400,10,0,0);
    numbers[7] = create_sprite(seven_xpm,400,10,0,0);
    numbers[8] = create_sprite(eight_xpm,400,10,0,0);
    numbers[9] = create_sprite(nine_xpm,400,10,0,0);

    alloc_background();
 


    Sphere* sphere = create_sphere(400,400);
    Sprite* platform = create_sprite(paddle_xpm,400, 550,0,0);

    Sprite* lives_sprite[3];
    
    for (uint8_t i = 0; i < 3; i++)
    {
        lives_sprite[i] = create_sprite(heart00_xpm,vmi_p.XResolution - 210 + i * 32,16,0,0);
    }

    AnimSprite* explosion[30];
    Brick* bricks[30];
    uint16_t x = 64;uint16_t y = 150;
    for(int i = 0; i < 3 ; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            bricks[10 * i + j] = create_brick(x * (j + 1),32 * i + y);
        }
    }
    
    
    //---------------------------------------

    int ipc_status,r;
    message msg;
    while (scancode != ESC_KEY) {
        // Get a request message
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
        printf("driver_receive failed with: %d", r);
        continue;
        }
        if (is_ipc_notify(ipc_status)) { // received notification
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: // hardware interrupt notification
            if (msg.m_notify.interrupts & keyboard_bit_mask) { // subscribed interrupt
                kbc_get_scancode();
                kbc_verify_scancode();
            }
            if (msg.m_notify.interrupts & timer_bit_mask) {
                if(!lives)
                {
                    game_over(true);
                }
                else
                {
                    if(init)
                    {
                        draw_background(true);
                        init = false;
                    }
                    
                    
                    reset_to_background();

                    sphere->old_x = sphere->x;
                    sphere->old_y = sphere->y;

                    sphere->x += sphere->dx * 3;
                    sphere->y += sphere->dy * 3;

                    if(sphere->y >= vmi_p.YResolution)
                        sphere->y = 0;
                    if(sphere->x >= vmi_p.XResolution)
                        sphere->x = 0;


                    if (complete_scancode){
                    switch(scancode)
                    {
                        case A_KEY:
                            //if x <= origin + 5
                            if(!(platform->x - 5 <= 0))
                                platform->x -= 6.0f;
                            break;
                        case D_KEY:
                            if(!(platform->x + 5 + platform->width >= vmi_p.XResolution))
                                platform->x += 6.0f;
                            break;
                    }
                    }
                    //replace sphere->x + 16 with actual meaningfull numbers k thx, k yhx
                    if(sphere->x + 16 >= vmi_p.XResolution || sphere->x <= 0)
                        sphere->dx *= -1;
                    if(sphere->y + 16 >= vmi_p.YResolution || sphere->y <= 0 || (sphere->x >= platform->x && sphere->x <= platform->x + platform->width && sphere->y >= platform->y && sphere->y <= platform->y + platform->height))
                        sphere->dy *= -1;
                    if(sphere->y >= platform->y + platform->height)
                    {
                        sphere->x = 400;
                        sphere->y = 400;
                        lives--;
                    }
                    

                    bool no_colisions = true;

                    draw_sphere(sphere);
                    for(int i = 0; i < 30; i++)
                    {   
                        
                        if(no_colisions && !bricks[i]->is_destroyed && (bricks[i]->x <= sphere->x && bricks[i]->x + bricks[i]->width >= sphere->x && bricks[i]->y <= sphere->y && bricks[i]->y + bricks[i]->height >= sphere->y))
                        {
                            
                            bricks[i]->is_destroyed = true;
                            no_colisions = false;


                            //left side
                            if(sphere->old_x <= bricks[i]->x && sphere->x  >= bricks[i]->x)
                                sphere->dx *= -1;
                            //right side
                            else if(sphere->old_x >= bricks[i]->x + bricks[i]->width && sphere->x <= bricks[i]->x + bricks[i]->width)
                                sphere->dx *= -1;
                            //up side
                            else if(sphere->old_y <= bricks[i]->y && sphere->y  >= bricks[i]->y)
                                sphere->dy *= -1;
                            //down side
                            else if(sphere->old_y > bricks[i]->y + bricks[i]->height && sphere->y <= bricks[i]->y + bricks[i]->height)
                                sphere->dy *= -1;
                            


                            score += 1;
                            explosion[i] = create_animSprite(bricks[i]->x,bricks[i]->y,8,explosao0,explosao1,explosao2,explosao3,explosao4,explosao5,explosao6,explosao7);
                        }
                        if(!bricks[i]->is_destroyed)
                        {
                            draw_brick(bricks[i]);
                        }
                        else
                        {
                            if(get_cur_fig(explosion[i]) != 7)
                                animate_sprite(explosion[i]);
                        }
                        
                    }

                    //lives

                    for(uint8_t i = 0; i < lives; i++)
                        draw_sprite(lives_sprite[i]);

                    draw_sprite(platform);

                    draw_score(score,numbers);
                    
                    
                    double_buff();
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
    
    if (kbd_unsubscribe_int())
        return 1;
    if (timer_unsubscribe_int())
        return 1;

    for(int i = 0 ; i < 10; i++)
        destroy_sprite(numbers[i]); 
    destroy_sprite(platform);


    return 0;
}
