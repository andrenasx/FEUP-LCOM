#include "sprite.h"

/** Creates a new sprite with pixmap "pic", with specified
* position (within the screen limits) and speed;
* Does not draw the sprite on the screen
* Returns NULL on invalid pixmap.
*/

Sprite *create_sprite(xpm_image_t img, int x, int y, int xspeed, int yspeed) {
//allocate space for the "object"
Sprite *sp = (Sprite *) malloc ( sizeof(Sprite));
//xpm_image_t img;
if( sp == NULL )
  return NULL;
// read the sprite pixmap
sp->map = img.bytes;
if( sp->map == NULL ) {
  free(sp);
  return NULL;
}
sp->x=x;
sp->y=y;
sp->width = img.width;
sp->height=img.height;
sp->xspeed=xspeed;
sp->yspeed=yspeed;

return sp;
}

void destroy_sprite(Sprite *sp) {
if( sp == NULL )
return;
if( sp ->map )
free(sp->map);
free(sp);
sp = NULL; // XXX: pointer is passed by value
// should do this @ the caller
}

int draw_sprite(Sprite *sp, char *base) {
  uint32_t transparent = xpm_transparency_color(XPM_8_8_8_8);
  uint32_t* color = (uint32_t*)sp->map;

  for(int i=0; i<sp->height; i++){
    if((sp->y +i)>= (int)get_v_res()) continue;
    else if((sp->y + i)<=0) break;
    for(int j=0; j<sp->width; j++){
      if((sp->x+j)>= (int)get_h_res()) continue;
      else if((sp->x + j) <=0) break;
      if(*color!=transparent){
        if(change_pixel_color(sp->x + j, sp->y + i, *color)!=0){
          return 1;
        }
      }
      
      color++;
    }
  }

  return 0;
}

int erase_sprite(Sprite *sp, char *base){
  uint32_t transparent = xpm_transparency_color(XPM_8_8_8_8);
  uint32_t* color = (uint32_t*)sp->map;
  
  for(int i=0;i<sp->height;i++){
    if((sp->y +i)>= (int)get_v_res()) continue;
    else if((sp->y + i)<=0) break;
    for(int j=0;j<sp->width;j++){
      if((sp->x +j)>= (int)get_h_res()) continue;
      else if((sp->x + j)<=0) break;
      if(*color!=transparent){
        if(change_pixel_color(sp->x + j, sp->y + i, 0x00)!=0){
          return 1;
        }
      }
      color++;
    }
  }
  return 0;
}
