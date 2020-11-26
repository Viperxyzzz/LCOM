#include "mouse.h"




bool complete = false;
static int hook_id = 0;
static uint8_t packets[3];
static uint8_t packet = 0;
static uint8_t counter = 0;
struct packet mouse_packets;


int (mouse_subscribe_int)(uint8_t *bit_no)
{
    hook_id = IRQ12;
    *bit_no = IRQ12;
    if(sys_irqsetpolicy(IRQ12,IRQ_REENABLE | IRQ_EXCLUSIVE,&hook_id))
    {
        return 1;
    }
    return 0;
}
int (mouse_unsubscribe_int)()
{
    if(sys_irqrmpolicy(&hook_id))
    {
        return 1;
    }
    return 0;
}


void (mouse_ih)()
{
    util_sys_inb(OUT_BUFF,&packet);

}


int (analize_buffer)()
{
  uint8_t status = 0;
  //getting status
  if (util_sys_inb(STATUS_REG,&status))
  {
    return 1;
  }
  //if output buffer is empty 
  if(!(status & OBUFFER_FULL))
  {
    return 1;
  }

  mouse_ih();


  if(status & (PARITY | TIMEOUT))
  {
    return 1;
  }
  return 0;
}


int (process_packet)()
{
    //we're starting a byte
    if(counter == 0)
    {
        packets[0] = packet;
        counter++;
    }
    else if (counter == 1)
    {
        packets[1] = packet;
        counter++;
    }
    else if (counter == 2)
    {
        packets[2] = packet;
        counter = 0;
        complete = true;
    }
    else
        return 1;
    return 0;
}
int (parse_packet)()
{
    if(complete)
    {
        mouse_packets.bytes[0] = packets[0];
        mouse_packets.bytes[1] = packets[1];
        mouse_packets.bytes[2] = packets[2];
        
        
        mouse_packets.delta_x = packets[1];
        mouse_packets.delta_y = packets[2];


        mouse_packets.lb = packets[0] & BIT(0);
        mouse_packets.rb = packets[0] & BIT(1);
        mouse_packets.mb = packets[0] & BIT(2);

        mouse_packets.x_ov = packets[0] & BIT(6);
        mouse_packets.y_ov = packets[0] & BIT(7);

        complete = false;

        return 0;
    }
    return 1;
}
