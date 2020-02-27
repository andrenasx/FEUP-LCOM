#ifndef __KEYBOARD_H_
#define __KEYBOARD_H_

#include <stdbool.h>
#include <stdint.h>
#include "i8254.h"
#include "i8042.h"

/**
 * @brief Subscribes keyboard interrupts
 * @param bit_no Contains address of kbd interrupt bit set to 1
 * @return 0 upon success, 1 otherwise
 */
int(kbd_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes  keyboard interrupts
 * @return 0 upon success, 1 otherwise
 */
int(kbd_unsubscribe_int)();

/**
 * @brief Keyboard interrupt handler
 */
void (kbc_ih)();
/**
 *
 * @return 0 upon success, 1 otherwise
 */
int (kbd_enable)();

#endif


