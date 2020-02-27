#include "colision.h"

extern bool shoot, mousePressed;

bool checkColision(Sprite *s1, Sprite *s2){
  return !(s1->x + s1->width < s2->x || s2->x + s2->width < s1->x || s1->y + s1->height < s2->y || s2->y + s2->height < s1->y);
}

void resetBorderColision(Sprite* sp){
  if(sp->x<=0)
    sp->x=1;
  else if(sp->x + sp->width >= get_h_res())
    sp->x=get_h_res()-sp->width-1;
  if(sp->y<=0)
    sp->y=1;
  else if(sp->y + sp->height >= get_v_res())
    sp->y=get_v_res()-sp->height-1;
}

bool checkAsteroidUFOColision(Game* game){
  for (int i=0;i<50;i++){
    if(game->gamesprites->asteroids[i]!=NULL){
      if(checkColision(game->gamesprites->ufo,game->gamesprites->asteroids[i])){
        resetGame();
        game->state=GAMEOVER;
        return true;
      }
    }
  }
  return false;
}

void checkBulletAsteroidColision(Game* game){
  if(shoot){
    for(int k=0;k<50;k++){
      if(game->gamesprites->asteroids[49-k]!=NULL){
        if(checkColision(game->gamesprites->aim,game->gamesprites->asteroids[49-k])){
          int x=game->gamesprites->asteroids[49-k]->x;
          int y=game->gamesprites->asteroids[49-k]->y;
          uint8_t* map = game->gamesprites->asteroids[49-k]->map;
          destroy_sprite(game->gamesprites->asteroids[49-k]);
          game->gamesprites->asteroids[49-k]=NULL;
          if(map==game->images.asteroidL.bytes){
            createAsteroid(game, 2, x, y);
            createAsteroid(game, 2, x, y);
            game->score+=10;
          }
          else if(map==game->images.asteroidM.bytes){
            createAsteroid(game, 1, x, y);
            createAsteroid(game, 1, x, y);
            game->score+=20;
          }
          else if(map==game->images.asteroidS.bytes){
            game->score+=40;
          }
          return;
        }
      }
    }
    game->score-=50;
    if(game->score<=0)
      game->score=0;
  }
}

void mouseMainMenuChange(Game* game){
  int x = game->gamesprites->aim->x+(game->gamesprites->aim->width)/2;
  int y = game->gamesprites->aim->y+(game->gamesprites->aim->height)/2;

  if(x > 478 && x < 673 && ((y > 395 && y < 465) || (y > 500 && y < 570) || (y > 600 && y < 670))){
    game->gamesprites->aim->map=game->images.aim_ready.bytes;
  }
  else{
    game->gamesprites->aim->map=game->images.aim_wait.bytes;
  }
  if(mousePressed == true && x > 478 && x < 673){
    if(y > 395 && y < 465){
      game->state=GAME;
    }
    else if(y > 500 && y < 570){
      game->state=HELP;
    }
    else if(y > 600 && y < 670){
      game->state=END;
    }
  }
}

void mouseMenuChange(Game* game){
  int x = game->gamesprites->aim->x+(game->gamesprites->aim->width)/2;
  int y = game->gamesprites->aim->y+(game->gamesprites->aim->height)/2;

  if(x > 288 && x < 865 && y > 737 && y < 790){
    game->gamesprites->aim->map=game->images.aim_ready.bytes;
    if(mousePressed){
      game->state=MENU;
      game->score=0;
    }
  }
  else{
    game->gamesprites->aim->map=game->images.aim_wait.bytes;
  }
}
