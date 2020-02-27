#pragma once
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>
#include "game.h"
#include "timer.h"
#include "mouse.h"
#include "colision.h"

/**
 * @brief create game sprite
 * @param game where aim sprite will be stored
 */
void createAim(Game* game);

/**
 * @brief To update aim sprite accordingly with mouse movement
 * @param pp Packet with mouse info
 * @param game Struct with aim sprite
 */
void updateMouse(struct packet pp, Game* game);

/**
 * @brief resets shoot timer to make shooting unavailable again
 * @param game
 */
void resetShot(Game* game);

/**
 * @brief make shooting available every half second
 * @param game
 */
void shoot_time_handler(Game* game);

/**
 * @brief draw aim sprite in updated coordinates
 * @param game Strcut where aim sprite is located
 */
void moveMouse(Game* game);
