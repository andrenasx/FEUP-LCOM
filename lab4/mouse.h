#ifndef __KEYBOARD_H_
#define __KEYBOARD_H_

#include <stdbool.h>
#include <stdint.h>

int(mouse_subscribe_int)(uint32_t *bit_no);
int(mouse_unsubscribe_int)();
void (mouse_ih)();
void build_packet(uint8_t *byte, uint8_t *pos);
int (mouse_parse_packet)(uint8_t *byte, struct packet *packet);
int (write_command)(uint8_t port, uint8_t cmd);
int (write_mouse_command)(uint8_t cmd);
void (statemachine)(uint8_t x_len, uint8_t tolerance, struct packet *packet);

#endif
