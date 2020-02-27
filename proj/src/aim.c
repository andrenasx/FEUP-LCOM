#include "aim.h"

unsigned int shoot_timer=0;
bool shoot, shoot_available, mousePressed;

void createAim(Game* game){
  game->gamesprites->aim=create_sprite(game->images.aim_wait,300,300,1,1);
}

void  updateMouse(struct packet pp, Game* game){
  mousePressed=false;

  if(pp.delta_x != 0 || pp.delta_y != 0){
    game->gamesprites->aim->x += pp.delta_x;
    game->gamesprites->aim->y -= pp.delta_y;
    resetBorderColision(game->gamesprites->aim);
  }

  if(pp.lb==1){
    mousePressed=true;
    if(shoot_available){
      shoot=true;
    }
  }
}

void moveMouse(Game* game){
  draw_sprite(game->gamesprites->aim, get_double_buffer());
}

void shoot_time_handler(Game* game){
  shoot_timer++;
  if(shoot_timer%30==0){
    shoot_available=true;
    game->gamesprites->aim->map = game->images.aim_ready.bytes;
    draw_sprite(game->gamesprites->aim, get_double_buffer());
  }
}

void resetShot(Game* game){
  if(shoot){
    game->gamesprites->aim->map = game->images.aim_wait.bytes;
    draw_sprite(game->gamesprites->aim, get_double_buffer());
    shoot = false;
    shoot_available = false;
    shoot_timer = 0;
  }
}
