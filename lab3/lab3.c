#include <lcom/lcf.h>

#include <lcom/lab3.h>
#include <lcom/timer.h>

#include <stdbool.h>
#include <stdint.h>

#include "keyboard.h"
#include "i8042.h"
#include "i8254.h"


extern unsigned long timer_counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  
  uint8_t bit_no = IRQ1;
  int     irq_set = BIT(IRQ1);


  if (kbd_subscribe_int(&bit_no))
  {
    return 1;
  }


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
            if (complete_scancode){
              print_scancode();
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
  {
      return 1;
  }

/*
  if (kbd_print_no_sysinb(no_of_calls))
  {
		return 1;
  }
*/


  return 0;
}

int(kbd_test_poll)() {
  while (scancode != ESC_KEY)
  {
    if(kbc_get_scancode())
    {
      if(tickdelay(micros_to_ticks(DELAY_US)))
        return 1;
      continue;
    }
    kbc_verify_scancode();
    if(complete_scancode)
    {
      print_scancode();
    }
  }

  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  uint8_t timer_bit_mask = TIMER0_IRQ;
  uint8_t kbd_bit_mask   = IRQ1;
  uint8_t wait = 0;


  int irq_set = BIT(timer_bit_mask);
  int kbd_set = BIT(kbd_bit_mask);

  if(timer_subscribe_int(&timer_bit_mask))
  {
    return 1;
  }

  if(kbd_subscribe_int(&kbd_bit_mask))
  {
    return 1;
  }

  int ipc_status,r;
  message msg;
  while ((scancode != ESC_KEY) && (wait != n)) {
    // Get a request message
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { // received notification
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: // hardware interrupt notification
          if(msg.m_notify.interrupts & irq_set){
            timer_int_handler();
            if (timer_counter % 60 == 0)
            {
              wait++;
            }
            
          }
          if (msg.m_notify.interrupts & kbd_set) { // subscribed interrupt
            wait = 0;
            kbc_get_scancode();
            kbc_verify_scancode();
            if (complete_scancode){
              print_scancode();
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
  if(kbd_unsubscribe_int())
  {
    return 1;
  }
  if(timer_unsubscribe_int())
  {
    return 0;
  }


  return 0;
}