// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you
#include "videocard.h"
#include "keyboard.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {

  if(vg_init(mode) == NULL)
    return 1;
  sleep(delay);
  vg_exit();
  return 1;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
  
  if(vg_init(mode) == NULL)
    return 1;
  if(vg_draw_rectangle(x,y,width,height,color))
    return 1;
  
  uint8_t bit_no = IRQ1;
  int irq_set = BIT(IRQ1);

  if(kbd_subscribe_int(&bit_no))
    return 1;
  

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
          if (msg.m_notify.interrupts & irq_set) { // subscribed interrupt
            kbc_get_scancode();
            kbc_verify_scancode();
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


  if(kbd_unsubscribe_int())
    return 1;

  if(vg_exit())
    return 1;

  return 1;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  //NOT DONE
  if(vg_init(mode) == NULL)
    return 1;
  return 1;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  uint16_t mode = 0x105;
  if(vg_init(mode) == NULL)
    return 1;
  if(vg_read_xpm(xpm,x, y))
    return 1;
  
  uint8_t bit_no = IRQ1;
  int irq_set = BIT(IRQ1);

  if(kbd_subscribe_int(&bit_no))
    return 1;
  

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
          if (msg.m_notify.interrupts & irq_set) { // subscribed interrupt
            kbc_get_scancode();
            kbc_verify_scancode();
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


  if(kbd_unsubscribe_int())
    return 1;

  if(vg_exit())
    return 1;

  return 1;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
