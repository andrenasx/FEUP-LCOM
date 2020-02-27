#include <sys/mman.h>
#include <lcom/vbe.h>
#include "video_graph.h"

static void *video_mem;
static void *double_buffer;
static vbe_mode_info_t inf;
static unsigned h_res;	        /* Horizontal resolution in pixels */
static unsigned v_res;	        /* Vertical resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */
static unsigned bytes_per_pixel; /* Number of VRAM bytes per pixel */

char * get_video_mem(){
  return (char*)video_mem;
}

char* get_double_buffer(){
  return (char *)double_buffer;
}

void swapBuffer(){
  memcpy(video_mem, double_buffer, h_res*v_res*bytes_per_pixel);
}

int get_h_res(){
  return h_res;
}

int get_v_res(){
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

  reg86_t r86;
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

  //Double Buffer
  double_buffer = malloc(vram_size);

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

  if(x>=h_res || y>=v_res){
    return 1;
  }

  uint8_t *pixel_pointer;

  //pixel_pointer = (uint8_t*)video_mem + (x * bytes_per_pixel) + (y * h_res *bytes_per_pixel);
  pixel_pointer = (uint8_t*)double_buffer + (x * bytes_per_pixel) + (y * h_res *bytes_per_pixel);
  uint8_t change;

  for(unsigned i =0; i< bytes_per_pixel; i++){
    change = color & 0xFF;
    *(pixel_pointer + i) = change;
    color = color >> 8;
  }

  return 0;
}

int (draw_xpm)(xpm_image_t img, uint16_t x, uint16_t y){

  uint32_t transparent = xpm_transparency_color(XPM_8_8_8_8);
  uint32_t* color = (uint32_t*)img.bytes;

  for(int i=0; i<img.height; i++){
    for(int j=0; j<img.width; j++){
      if(*color!=transparent){
        if(change_pixel_color(x + j,y + i, *color)!=0){
          return 1;
        }
      }
      
      color++;
    }
  }

  return 0;
}
