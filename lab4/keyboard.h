#ifndef KEYBOARD_H
#define KEYBOARD_H


#include <lcom/lcf.h>
#include "i8042.h"

extern uint8_t scancode;
extern bool    complete_scancode;


int (kbd_subscribe_int)(uint8_t *bit_no);
int (kbd_unsubscribe_int)();
int (kbc_get_scancode)();
void (kbc_verify_scancode)();
void (print_scancode)();

#endif
