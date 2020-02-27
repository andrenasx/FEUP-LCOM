#pragma once
#include <lcom/lcf.h>
#include <stdint.h>
#include "video_graph.h"
#include "video_macros.h"

/**
 * @brief Struct to keep sprite info
 */
typedef struct {
int x, y; // current position
int width, height; // dimensions
int xspeed, yspeed; // current speed
uint8_t *map; // the pixmap
} Sprite;

/**
 *
 * @param img XPM image
 * @param x Coordinate x of sprite
 * @param y Coordinate y of sprite
 * @param xspeed Speed alog x of sprite
 * @param yspeed Speed along y of sprite
 * @return
 */
Sprite * create_sprite(xpm_image_t img, int x, int y,int xspeed, int yspeed);

/**
 *  @brief Destroy sprite
 * @param sp Sprite to use in function
 */
void destroy_sprite(Sprite * sp);

/**
 *
 * @param sp Sprite to use in function
 * @param base Memory address to draw
 * @return 0 upon success, 1 otherwise
 */
int draw_sprite(Sprite *sp, char *base);

/**
 * @brief Erase sprite
 * @param sp Sprite to use in function
 * @param base Memory address to draw                                                               
 * @return 0 upon success, 1 otherwise
 */
int erase_sprite(Sprite *sp, char *base);
