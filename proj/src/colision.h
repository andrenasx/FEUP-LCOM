#pragma once
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>
#include "game.h"

/**
 * @brief Check collison between two sprites
 * @param s1 Sprite
 * @param s2 Sprite
 * @return True if collision occured, false otherwise
 */
bool checkColision(Sprite *s1, Sprite *s2);

/**
 * @brief If sprite crosses screen border it returns to screen
 * @param sp Sprite to be analyzed
 */
void resetBorderColision(Sprite *sp);

/**
 * @brief Checks if collision between Asteroid and UFO occured
 * @param game struct where game info is located
 * @return True if collision occured, false otherwise
 */
bool checkAsteroidUFOColision(Game* game);

/**
 * @brief Check collision between bullet and asteroids
 * @param game Struct where variable of the game are located
 */
void checkBulletAsteroidColision(Game* game);

/**
 *  @brief Navigate from main menu to any of the other 3 if mouse conditions are true
 * @param game struct where game info is located
 */
void mouseMainMenuChange(Game* game);

/**
 * @brief Return to main menu if mouse conditions are true
 * @param game Struct where game info is located
 */
void mouseMenuChange(Game* game);
