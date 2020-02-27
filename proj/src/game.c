#include "game.h"

//Game variables
extern unsigned int timer_counter, shoot_timer;
static Game* game;

void loadGameXPMs(){
  game = (Game*)malloc(sizeof(Game));
  game->gamesprites = (GameSps*)malloc(sizeof(GameSps));
  xpm_load(aimWait_xpm, XPM_8_8_8_8, &game->images.aim_wait);
  xpm_load(aimReady_xpm, XPM_8_8_8_8, &game->images.aim_ready);
  xpm_load(asteroidL_xpm, XPM_8_8_8_8, &game->images.asteroidL);
  xpm_load(asteroidM_xpm, XPM_8_8_8_8, &game->images.asteroidM);
  xpm_load(asteroidS_xpm, XPM_8_8_8_8, &game->images.asteroidS);
  xpm_load(UFO_xpm, XPM_8_8_8_8, &game->images.ufo);
  xpm_load(score_xpm, XPM_8_8_8_8, &game->images.scoreP);
  xpm_load(background_xpm, XPM_8_8_8_8, &game->images.background);
  xpm_load(num0_xpm, XPM_8_8_8_8, &game->images.num0);
  xpm_load(num1_xpm, XPM_8_8_8_8, &game->images.num1);
  xpm_load(num2_xpm, XPM_8_8_8_8, &game->images.num2);
  xpm_load(num3_xpm, XPM_8_8_8_8, &game->images.num3);
  xpm_load(num4_xpm, XPM_8_8_8_8, &game->images.num4);
  xpm_load(num5_xpm, XPM_8_8_8_8, &game->images.num5);
  xpm_load(num6_xpm, XPM_8_8_8_8, &game->images.num6);
  xpm_load(num7_xpm, XPM_8_8_8_8, &game->images.num7);
  xpm_load(num8_xpm, XPM_8_8_8_8, &game->images.num8);
  xpm_load(num9_xpm, XPM_8_8_8_8, &game->images.num9);
  xpm_load(num0L_xpm, XPM_8_8_8_8, &game->images.num0L);
  xpm_load(num1L_xpm, XPM_8_8_8_8, &game->images.num1L);
  xpm_load(num2L_xpm, XPM_8_8_8_8, &game->images.num2L);
  xpm_load(num3L_xpm, XPM_8_8_8_8, &game->images.num3L);
  xpm_load(num4L_xpm, XPM_8_8_8_8, &game->images.num4L);
  xpm_load(num5L_xpm, XPM_8_8_8_8, &game->images.num5L);
  xpm_load(num6L_xpm, XPM_8_8_8_8, &game->images.num6L);
  xpm_load(num7L_xpm, XPM_8_8_8_8, &game->images.num7L);
  xpm_load(num8L_xpm, XPM_8_8_8_8, &game->images.num8L);
  xpm_load(num9L_xpm, XPM_8_8_8_8, &game->images.num9L);
  xpm_load(mainmenu_xpm, XPM_8_8_8_8, &game->images.mainmenu);
  xpm_load(instructions_xpm, XPM_8_8_8_8, &game->images.instructions);
  xpm_load(gameover_xpm, XPM_8_8_8_8, &game->images.gameover);
}

Game* getGame(){
  return game;
}

void startGame(){
  game->score = 0;
  game->state=MENU;
  createUFO(game);
  createAim(game);
  createAsteroidsArray(game);
}

void drawBackground(){
  draw_xpm(game->images.background, 0, 0);
}

void drawMainMenu(){
  draw_xpm(game->images.mainmenu, 0, 0);
}

void drawHelp(){
  draw_xpm(game->images.instructions, 0, 0);
}

void drawGameOver(){
  draw_xpm(game->images.gameover, 0, 0);
}

void drawScore(){
  draw_xpm(game->images.scoreP, 0, 0);
  int temp = game->score, x=175;
  while(temp>=0){
    int num = temp % 10;
    switch(num){
      case 0:
        draw_xpm(game->images.num0, x, 0);
        break;
      case 1:
        draw_xpm(game->images.num1, x, 0);
        break;
      case 2:
        draw_xpm(game->images.num2, x, 0);
        break;
      case 3:
        draw_xpm(game->images.num3, x, 0);
        break;
      case 4:
        draw_xpm(game->images.num4, x, 0);
        break;
      case 5:
        draw_xpm(game->images.num5, x, 0);
        break;
      case 6:
        draw_xpm(game->images.num6, x, 0);
        break;
      case 7:
        draw_xpm(game->images.num7, x, 0);
        break;
      case 8:
        draw_xpm(game->images.num8, x, 0);
        break;
      case 9:
        draw_xpm(game->images.num9, x, 0);
        break;
      default:
        break;
    }
    if(temp<10){
      break;
    }
    else{
      temp/=10;
      x-=20;
    }
  }
}

void drawGameOverScore(){
  int temp = game->score, count=0, x;

  while (temp != 0) {
    temp /= 10;
    count++;
  }
  switch(count){
    case 1:
      x=550;
      break;
    case 2:
      x=580;
      break;
    case 3:
      x=610;
      break;
    case 4:
      x=640;
      break;
    case 5:
      x=670;
      break;
    default:
      x=640;
      break;
  }

  temp=game->score;
  while(temp>=0){
    int num = temp % 10;
    switch(num){
      case 0:
        draw_xpm(game->images.num0L, x, 450);
        break;
      case 1:
        draw_xpm(game->images.num1L, x, 450);
        break;
      case 2:
        draw_xpm(game->images.num2L, x, 450);
        break;
      case 3:
        draw_xpm(game->images.num3L, x, 450);
        break;
      case 4:
        draw_xpm(game->images.num4L, x, 450);
        break;
      case 5:
        draw_xpm(game->images.num5L, x, 450);
        break;
      case 6:
        draw_xpm(game->images.num6L, x, 450);
        break;
      case 7:
        draw_xpm(game->images.num7L, x, 450);
        break;
      case 8:
        draw_xpm(game->images.num8L, x, 450);
        break;
      case 9:
        draw_xpm(game->images.num9L, x, 450);
        break;
      default:
        break;
    }
    if(temp<10){
      break;
    }
    else{
      temp/=10;
      x-=60;
    }
  }
}

void resetGame(){
  shoot_timer=0;
  timer_counter=0;
  stopUFO();
  game->gamesprites->ufo->x=550;
  game->gamesprites->ufo->y=400;
  game->gamesprites->aim->map=game->images.aim_ready.bytes;
  for(int i=0;i<50;i++){
    if(game->gamesprites->asteroids[i]!=NULL){
      destroy_sprite(game->gamesprites->asteroids[i]);
      game->gamesprites->asteroids[i]=NULL;
    }
  }
}

void destroyGame(){
  destroy_sprite(game->gamesprites->ufo);
  destroy_sprite(game->gamesprites->aim);
  for(int i=0;i<50;i++){
    if(game->gamesprites->asteroids[i]!=NULL){
      destroy_sprite(game->gamesprites->asteroids[i]);
      game->gamesprites->asteroids[i]=NULL;
    }
  }
  // for(int i=0;i<30;i++){
  //   if(bullets[i]!=NULL){
  //     destroy_sprite(bullets[i]);
  //   }
  // }
}
