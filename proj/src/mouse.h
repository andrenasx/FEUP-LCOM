#include <stdbool.h>
#include <stdint.h>


/**
 * @brief Subscribes keyboard interrupts
 * @param bit_no Contains address of mouse interrupt bit set to 1
 * @return 0 upon success, 1 otherwise
 */
int(mouse_subscribe_int)(uint32_t *bit_no);

/**
 * @brief Unsubscribes mouse  interrupts
 * @return 0 upon success, 1 otherwise
 */
int(mouse_unsubscribe_int)();

/**
 * @brief Mouse interrupt handler
 */
void (mouse_ih)();

/**
 * @brief Add byte from mouse to mouse bytes arrya
 * @param byte Byte to add to array
 * @param pos Position in which the byte will be add
 */
void build_packet(uint8_t *byte, uint8_t *pos);

/**
 * @brief Create a struct with mouse movement info
 * @param byte Memory address of bytes array
 * @param pp Memory address os struct packet
 * @return 0 upon success, 1 otherwise
 */
int (mouse_parse_packet)(uint8_t *byte, struct packet *pp);

/**
 *
 * @param port
 * @param cmd
 * @return
 */
int (write_command)(uint8_t port, uint8_t cmd);

/**
 *
 * @param cmd
 * @return
 */
int (write_mouse_command)(uint8_t cmd);

/**
 * @brief Function for lab4
 * @param x_len
 * @param tolerance
 * @param pp
 */
void (statemachine)(uint8_t x_len, uint8_t tolerance, struct packet *pp);

