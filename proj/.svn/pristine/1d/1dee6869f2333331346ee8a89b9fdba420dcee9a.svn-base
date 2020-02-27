#pragma once
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>
#include "sprite.h"

/**
 * @brief ENUM with possible states of the game
 */
enum game_state {MENU, HELP, GAME, GAMEOVER, END};

/**
 * @brief Struct with game sprites
 */
typedef struct{
  Sprite* ufo;
  Sprite* aim;
  Sprite** asteroids;
} GameSps;

/**
 * @brief Strcut with XPMs used in the game
 */
typedef struct{
  xpm_image_t aim_wait, aim_ready, asteroidL, asteroidM, asteroidS, ufo, scoreP, background, num0,num1,num2,num3,num4,num5,num6,num7,num8,num9,num0L,num1L,num2L,num3L,num4L,num5L,num6L,num7L,num8L,num9L, mainmenu, instructions, gameover, playButton, helpButton, exitButton;
} Images;

/**
 * @brief Game main struct containing all game variables
 */
typedef struct{
  GameSps* gamesprites;
  Images images;
  enum game_state state;
  int score;
} Game;

#include "images/UFO.xpm"
#include "images/aimWait.xpm"
#include "images/aimReady.xpm"
#include "images/asteroidL.xpm"
#include "images/asteroidM.xpm"
#include "images/asteroidS.xpm"
#include "images/score.xpm"
#include "images/background.xpm"
#include "images/mainmenu.xpm"
#include "images/instructions.xpm"
#include "images/gameover.xpm"
#include "images/num0.xpm"
#include "images/num1.xpm"
#include "images/num2.xpm"
#include "images/num3.xpm"
#include "images/num4.xpm"
#include "images/num5.xpm"
#include "images/num6.xpm"
#include "images/num7.xpm"
#include "images/num8.xpm"
#include "images/num9.xpm"
#include "images/num0L.xpm"
#include "images/num1L.xpm"
#include "images/num2L.xpm"
#include "images/num3L.xpm"
#include "images/num4L.xpm"
#include "images/num5L.xpm"
#include "images/num6L.xpm"
#include "images/num7L.xpm"
#include "images/num8L.xpm"
#include "images/num9L.xpm"
#include "asteroids.h"
#include "aim.h"
#include "ufo.h"

/**
 * @brief Loads all XPMs necessary for the game
 */
void loadGameXPMs();

/**
 *
 * @return Pointer to struct Game
 */
Game* getGame();

/**
 *@brief Assignes the initial values upon opening the game
 */
void startGame();

/**
 * @brief Draw Scare during game
 */
void drawScore();

/**
 * @brief Draw background during game
 */
void drawBackground();

/**
 * @brief Draw Main Menu
 */
void drawMainMenu();

/**
 * @brief Draw help, information about the game and how to play
 */
void drawHelp();

/**
 * @brief Draw score after gameover
 */
void drawGameOverScore();

/**
 *@brief Draw gameover
 */
void drawGameOver();

/**
 * @brief Afer game over game variable return initial state
 */
void resetGame();

/**
 *@brief Eliminates allocated memory
 */
void destroyGame();
