#include "ufo.h"

extern int kbd_code;
static bool up=false, down=false, right=false, left=false;

void createUFO(Game* game){
  game->gamesprites->ufo=create_sprite(game->images.ufo,550,400,5,5);
}

void updateUFO(){
  bool make = (kbd_code & 0x80) == 0;

  //W-Move Up, S-Down, A-Left, D-Right
  if(make){
    if(kbd_code == 0x11){ //W make code 
      up=true;
    }
    else if(kbd_code == 0x1F){  //S make code
      down=true;
    }
    else if(kbd_code == 0x1E){  //A make code
      left=true;
    }
    else if(kbd_code== 0x20){  //D make code
      right=true;
    }
  }
  else{
    if(kbd_code == 0x91){ //W break code
      up=false;
    }
    else if(kbd_code == 0x9F){  //S break code
      down=false;
    }
    else if(kbd_code == 0x9E){ //A break code
      left=false;
    }
    else if(kbd_code == 0xA0){  //D break code
      right=false;
    }
  }
}

void moveUFO(Game* game){
  if(up)
    game->gamesprites->ufo->y-=game->gamesprites->ufo->yspeed;
  if(down) 
    game->gamesprites->ufo->y+=game->gamesprites->ufo->yspeed;

  if(left)
    game->gamesprites->ufo->x-=game->gamesprites->ufo->xspeed;
  if(right) 
    game->gamesprites->ufo->x+=game->gamesprites->ufo->xspeed;

  resetBorderColision(game->gamesprites->ufo);

  draw_sprite(game->gamesprites->ufo, get_double_buffer());
}

void stopUFO(){
  up=false;
  down=false;
  right=false;
  left=false;
}
