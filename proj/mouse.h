#ifndef MOUSE_H
#define MOUSE_H

#include <lcom/lcf.h>
#include "i8042.h"

int (mouse_subscribe_int)();
int (mouse_unsubscribe_int)();
void (mouse_ih)();
int (analize_buffer)();
int (process_packet)();
void (parse_packet)();
void (analyze_gesture)(uint8_t x_len, uint8_t tolerance);
int (send_cmd_mouse)(uint8_t cmd);

extern struct packet mouse_packets;
extern bool complete;


#endif
