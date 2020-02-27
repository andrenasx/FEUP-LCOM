#pragma once
#include <lcom/lcf.h>
#include <lcom/lab5.h>
#include <stdbool.h>
#include <stdint.h>
#include <minix/syslib.h>
#include <minix/sysutil.h>
#include "video_macros.h"

/**
 * @brief Initialize video mode
 * @param mode Mode in which video mode will be initialized
 */
void *(vg_init)(uint16_t mode);

/**
 * @brief Get horizontal resolution in video mode
 * @return Horizontal resolution
 */
int get_h_res();

/**
 * @brief Get vertical resolution in video mode
 * @return Vertica resolution
 */
int get_v_res();

/**
 * @brief Get actual video memory
 * @return Actual video memory
 */
char * get_video_mem();

/**
 * @brief Get double buffer
 * @return Secundary buffer to where sprites and xpms will be drawn
 */
char * get_double_buffer();

/**
 * @brief Swap between buffers
 */
void swapBuffer();

/**
 * @brief Get bits occupied per pixel in VRAM
 * @return Bits occupied per pixel in VRAM
 */
unsigned get_bits_per_pixel();

/**
 * @brief Get bytes occupied per pixel in VRAM
 * @return Bytes occupied per pixel in VRAM
 */
unsigned get_bytes_per_pixel();

/**
 * @brief Change one pixel color
 * @param x Pixel x coordinate
 * @param y Pixel y coordinate
 * @param color New color of pixel
 * @return 0 if successful, 1 otherwise
 */
int (change_pixel_color)(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief Draws XPM at VRAM coordinates
 * @param img XPM to draw
 * @param x Value of x coordinate
 * @param y Value of y coordinate
 * @return 0 if successful, 1 otherwise
 */
int (draw_xpm)(xpm_image_t img, uint16_t x, uint16_t y);
