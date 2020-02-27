#pragma once
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>
#include "sprite.h"
#include "keyboard.h"
#include "colision.h"
#include "game.h"

/**
 * @brief Create UFO sprite
 * @param game Struct where UFO sprite will be located, and UFO xpm is located
 */
void createUFO(Game* game);

/**
 * @brief Determine if UFO will move up, down, right or left accordingly to the keyboard interrupts recived
 */
void updateUFO();

/**
 * @brief Move UFO
 * @param game Struct where UFO sprite is located
 */
void moveUFO(Game* game);

/**
 * @brief UFO movement variable are set to false
 */
void stopUFO();
