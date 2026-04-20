/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld implementation.
 * 
 * @copyright Copyright (c) 2025
 */
#include <stdio.h>
#include <stdlib.h>

#include "ResourceManager.h"
#include "GameWorld.h"
#include "Types.h"
#include "Cannon.h"
#include "Building.h"
#include "Explosion.h"

const float GRAVITY = 500;

#include "raylib/raylib.h"
//#include "raylib/raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raylib/raygui.h"       // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

static void resolveCollisionBallBuildings( GameWorld *gw );

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld *createGameWorld( void ) {

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );

    float w = GetScreenWidth() / BUILDINGS_COUNT;

    for ( int i = 0; i < BUILDINGS_COUNT; i++ ) {
        float h = 100 + GetRandomValue( 0, 10 ) * 20;
        gw->buildings[i] = (Building) {
            .rect = {
                .x = w * i,
                .y = GetScreenHeight() - h,
                .width = w,
                .height = h
            },
            .color = i % 2 == 0 ? GRAY : LIGHTGRAY
        };
    }

    gw->cannon1 = createCannon( gw->buildings[2].rect.x, gw->buildings[2].rect.y - w, w, w, DEG2RAD * -45.0f, BLUE );
    gw->cannon2 = createCannon( gw->buildings[BUILDINGS_COUNT-3].rect.x, gw->buildings[BUILDINGS_COUNT-3].rect.y - w, w, w, DEG2RAD * -135.0f, RED );
    gw->currentCannon = gw->cannon1;

    gw->explosionCount = 0;

    return gw;

}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw ) {
    destroyCannon( gw->cannon1 );
    destroyCannon( gw->cannon2 );
    free( gw );
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void updateGameWorld( GameWorld *gw, float delta ) {
    updateCannon( gw->currentCannon, delta, gw );
    resolveCollisionBallBuildings( gw );
}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );

    for ( int i = 0; i < BUILDINGS_COUNT; i++ ) {
        drawBuilding( &gw->buildings[i] );
    }

    for ( int i = 0; i < MAX_EXPLOSIONS; i++ ) {
        drawExplosion( &gw->explosions[i] );
    }

    drawCannon( gw->cannon1 );
    drawCannon( gw->cannon2 );

    EndDrawing();

}

static void resolveCollisionBallBuildings( GameWorld *gw ) {

    Ball *ball = gw->currentCannon->ball;

    if ( ball != NULL && ball->alive ) {

        bool canExplode = true;

        for ( int i = 0; i < gw->explosionCount; i++ ) {
            Explosion *e = &gw->explosions[i];
            if ( CheckCollisionCircles( ball->pos, ball->radius / 2, e->pos, e->radius ) ) {
                canExplode = false;
                break;
            }
        }

        if ( canExplode ) {
            for ( int i = 0; i < BUILDINGS_COUNT; i++ ) {
                if ( CheckCollisionCircleRec( ball->pos, ball->radius, gw->buildings[i].rect ) ) {
                    ball->alive = false;
                    if ( gw->explosionCount < MAX_EXPLOSIONS ) {
                        gw->explosions[gw->explosionCount++] = (Explosion) {
                            .pos = ball->pos,
                            .radius = ball->radius * 4,
                            .color = WHITE
                        };
                    }
                    break;
                }
            }
        }

    }

}

void swapCurrentCannon( GameWorld *gw ) {
    if ( gw->currentCannon == gw->cannon1 ) {
        gw->currentCannon = gw->cannon2;
    } else {
        gw->currentCannon = gw->cannon1;
    }
}