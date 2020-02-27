#pragma once
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>
#include "game.h"

/**
 * @brief Allocate memory for array of Asteroids
 * @param game Struct where game info is located
 */
void createAsteroidsArray(Game* game);

/**
 * @brief Create asteroid with random size and initial x and y coordinates
 */
void createRandomAsteroid();

/**
 * @brief Create asteroid with random speed and with given size and coordinates
 * @param game Struct where asteroids array is stored
 * @param size Asteroid size
 * @param x Asteroid x coordinate
 * @param y Asteroid y coordinate
 */
void createAsteroid(Game* game, int size, int x, int y);

/**
 * @brief Draw all asteroids in updated positions
 * @param game Struct where game info is located
 */
void moveAsteroid(Game* game);
