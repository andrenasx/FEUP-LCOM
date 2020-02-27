#include <sys/mman.h>
#include <lcom/vbe.h>
#include "video_graph.h"

static void *video_mem;
static vbe_mode_info_t inf;
static unsigned h_res;	        /* Horizontal resolution in pixels */
static unsigned v_res;	        /* Vertical resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */
static unsigned bytes_per_pixel; /* Number of VRAM bytes per pixel */

unsigned get_h_res(){
  return h_res;
}

unsigned get_v_res(){
  return v_res;
}

unsigned get_bits_per_pixel(){
  return bits_per_pixel;
}

unsigned get_bytes_per_pixel(){
  return bytes_per_pixel;
}

void *(vg_init)(uint16_t mode){
  if (vbe_get_mode_info(mode, &inf) != 0)
  { // if Operation fail
    printf("vg_init(): failed to get mode \n");
    return NULL;
  }

  struct reg86 r86;
  int r;
  struct minix_mem_range mr;
  static unsigned int vram_base;
  static unsigned int vram_size;
  h_res = inf.XResolution;
  v_res = inf.YResolution;
  bits_per_pixel = inf.BitsPerPixel;
  bytes_per_pixel = (bits_per_pixel + 7) / 8;

  vram_base = inf.PhysBasePtr;
  vram_size = h_res * v_res * bytes_per_pixel;

  /* Allow memory mapping */
  mr.mr_base = (phys_bytes)vram_base;
  mr.mr_limit = mr.mr_base + vram_size;

  if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
  {
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    return NULL;
  }
  /* Map memory */
  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  if (video_mem == MAP_FAILED)
  {
    panic("couldn't map video memory");
    return NULL;
  }

  memset(&r86, 0, sizeof(r86));

  r86.ax = 0x4F02;
  r86.bx = BIT(14)|mode;
  r86.intno = 0x10;

  if (sys_int86(&r86) != OK)
  { // if Operation fail
    printf("vg_init(): sys_int86() failed \n");
    return NULL;
  }

  return video_mem;
}

int (change_pixel_color)(uint16_t x, uint16_t y, uint32_t color){

  if(x>h_res || y>v_res){
    return 1;
  }

  uint8_t *pixel_pointer;

  pixel_pointer = (uint8_t*)video_mem + (x * bytes_per_pixel) + (y * h_res *bytes_per_pixel);
  uint8_t change;

  for(unsigned i =0; i< bytes_per_pixel; i++){
    change = color & 0xFF;
    *(pixel_pointer + i) = change;
    color = color >> 8;
  }

  return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
  for(int i=0; i<len; i++){
      if(change_pixel_color(x + i,y,color)!=0){
        return 1;
      }
  }
  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){
  for(int i=0; i<height; i++){
    if(vg_draw_hline(x,y + i, width, color) != 0){
      return 1;
    }
  }
  return 0;
}

uint32_t(recs_color)(uint16_t row, uint16_t col, uint8_t no_rectangles, uint32_t first, uint8_t step){
  if (inf.BitsPerPixel==8){ //indexed color mode
    uint32_t c;
    c = (uint32_t)(first + (row * no_rectangles + col) * step) % (1 << bits_per_pixel);
    return c;

  } else{ //direct color mode
  
    uint32_t red = (((first>>inf.RedFieldPosition) & (1<<inf.RedMaskSize)-1) + col * step) % (1<<inf.RedMaskSize);

    uint32_t green = (((first>>inf.GreenFieldPosition) & (1<<inf.GreenMaskSize)-1) + row * step) % (1<<inf.GreenMaskSize);

    uint32_t blue = (((first>>inf.BlueFieldPosition) & (1<<inf.BlueMaskSize)-1) + (col+row) * step) % (1<<inf.BlueMaskSize);

    return (red << inf.RedFieldPosition | green << inf.GreenFieldPosition | blue << inf.BlueFieldPosition);
  }

  return 1;
}
