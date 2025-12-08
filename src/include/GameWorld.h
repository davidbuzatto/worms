/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld struct and function declarations.
 * 
 * @copyright Copyright (c) 2025
 */
#pragma once

#include "Types.h"
#define BUILDINGS_COUNT 40
#define MAX_EXPLOSIONS 300

extern const float GRAVITY;

typedef struct GameWorld {
    Cannon *cannon1;
    Cannon *cannon2;
    Cannon *currentCannon;
    Building buildings[BUILDINGS_COUNT];
    Explosion explosions[MAX_EXPLOSIONS];
    int explosionCount;
} GameWorld;

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void );

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw );

/**
 * @brief Reads user input and updates the state of the game.
 */
void updateGameWorld( GameWorld *gw, float delta );

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw );

void swapCurrentCannon( GameWorld *gw );