#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  
  uint8_t st;
  
  timer_get_conf(timer,&st);
  timer_display_conf(timer,st,field);
  

  return 0;
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {

  if (timer_set_frequency(timer,freq) != OK)
    return 1;

  return 0;
}


int(timer_test_int)(uint8_t time) {
  //Testing for invalid inputs
  if (time == 0)
  {
    printf("timer_test_int -> Time interval cannot be zero\n");
    return 1;
  }

  //Converting seconds to number of interrupts
  unsigned int interrupt_number_total = time * DEFAULT_FREQ;

  //Subscribing timer IRQ (IRQ line is masked according to irq_bitmask)
  uint8_t irq_bitmask;
  if (timer_subscribe_int(& irq_bitmask) != OK){
    printf("timer_subscribe_int -> Subscription didn't went through\n");
    return 1;
  }

  //Variables that will be used afterwards for driver_receive()
  int ipc_status;
  message msg;
  int request;


  //Cicle stops when we reach the end of the time interval
  while (counter < interrupt_number_total) {
    
    // Get a request message
    if ((request = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
      printf("driver_receive failed with: %d", request);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { // received notification
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: // hardware interrupt notification
          if (msg.m_notify.interrupts & irq_bitmask) { // subscribed interrupt

            //handler called to increment the global counter counter
            timer_int_handler();

            //timer_print_elapsed_time is called every second
            if (counter % 60 == 0){
              timer_print_elapsed_time();
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

  //unsubscribing timer IRQ
  if (timer_unsubscribe_int() != OK){
    printf("timer_test_int -> Error unsubscribing from the timer interrupt!\n");
    return 1;
  }
  return 0;
}
