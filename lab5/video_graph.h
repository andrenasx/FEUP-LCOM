#include <lcom/lcf.h>
#include <lcom/lab5.h>
#include <stdbool.h>
#include <stdint.h>
#include <minix/syslib.h>
#include <minix/sysutil.h>
#include "video_macros.h"

void *(vg_init)(uint16_t mode);
unsigned get_h_res();
unsigned get_v_res();
unsigned get_bits_per_pixel();
unsigned get_bytes_per_pixel();
int (change_pixel_color)(uint16_t x, uint16_t y, uint32_t color);
int (vb_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
uint32_t (recs_color)(uint16_t row, uint16_t col, uint8_t no_rectangles, uint32_t first, uint8_t step);
