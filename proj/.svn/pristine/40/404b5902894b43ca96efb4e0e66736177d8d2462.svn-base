#include "asteroids.h"

void createAsteroidsArray(Game* game){
  game->gamesprites->asteroids = (Sprite **) malloc(50*sizeof(Sprite*));
  for (int i=0; i<50; i++){
    game->gamesprites->asteroids[i]=NULL;
  }
}

void createAsteroid(Game* game, int size, int x, int y){
  int idx=0;
  while(game->gamesprites->asteroids[idx]!=NULL){
    idx++;
  }
  if(idx<50){
    srand(time(NULL));
    int xspeed = (rand() % 4) - (rand() % 4);
    int yspeed = (rand() % 4) - (rand() % 4);
    while (xspeed == 0){
      xspeed = (rand() % 4) - (rand() % 4);
    }
    while (yspeed == 0){
      yspeed = (rand() % 4) - (rand() % 4);
    }

    if(size == 3){
      game->gamesprites->asteroids[idx]=create_sprite(game->images.asteroidL, x, y, xspeed,yspeed);
    }
    else if(size == 2){
      game->gamesprites->asteroids[idx]=create_sprite(game->images.asteroidM, x, y, xspeed,yspeed);
    }
    else if(size == 1){
      game->gamesprites->asteroids[idx]=create_sprite(game->images.asteroidS,x, y, xspeed, yspeed);
    }
  }
}

void createRandomAsteroid(){  
  srand(time(NULL));
  int x = rand() % 1;
  int y = 0;
  if (x == 0)
    y = 1;

  int size = (rand() % 3) + 1;

  createAsteroid(getGame(), size, (rand()%get_h_res())*x, (rand()%get_v_res())*y);
}

void moveAsteroid(Game* game){
  for(int i=0; i<50; i++){
    if(game->gamesprites->asteroids[i]!=NULL){
      game->gamesprites->asteroids[i]->x += game->gamesprites->asteroids[i]->xspeed;
      game->gamesprites->asteroids[i]->y += game->gamesprites->asteroids[i]->yspeed;

      //If out of screen, move to opposite side
      if((game->gamesprites->asteroids[i]->x + game->gamesprites->asteroids[i]->width)<=0){
        game->gamesprites->asteroids[i]->x = get_h_res()-game->gamesprites->asteroids[i]->width;
      }
      else if((game->gamesprites->asteroids[i]->x + game->gamesprites->asteroids[i]->width) > get_h_res()){
        game->gamesprites->asteroids[i]->x=1;
      }
      else if((game->gamesprites->asteroids[i]->y + game->gamesprites->asteroids[i]->height)<=0){
        game->gamesprites->asteroids[i]->y=get_v_res()-game->gamesprites->asteroids[i]->height;
      }
      else if(game->gamesprites->asteroids[i]->y>get_v_res()){
        game->gamesprites->asteroids[i]->y=1;
      }
      draw_sprite(game->gamesprites->asteroids[i],get_double_buffer());
    }
  }
}
