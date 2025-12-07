#include <stdlib.h>
#include <math.h>

#include "raylib/raylib.h"
#include "Types.h"
#include "Ball.h"
#include "Cannon.h"
#include "GameWorld.h"

static void drawBallTrail( Cannon *cannon );

Cannon *createCannon( float x, float y, float width, float height, Color color ) {

    Cannon *new = (Cannon*) malloc( sizeof( Cannon ) );
    *new = (Cannon) { 0 };

    new->rect = (Rectangle) {
        .x = x,
        .y = y,
        .width = width,
        .height = height
    };

    new->color = color;
    new->mousePos = (Vector2) {0};
    new->preparing = false;
    new->fired = false;
    new->ball = NULL;

    return new;

}

void destroyCannon( Cannon *cannon ) {
    if ( cannon->ball != NULL ) {
        destroyBall( cannon->ball );
    }
    free( cannon );
}

void updateCannon( Cannon *cannon, float delta ) {
    
    if ( cannon->ball == NULL ) {

        if ( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) ) {
            cannon->preparing = true;
            cannon->fired = false;
        }

        if ( IsMouseButtonDown( MOUSE_BUTTON_LEFT ) ) {

            cannon->mousePos = GetMousePosition();

            cannon->magnitude = hypotf( 
                cannon->mousePos.x - cannon->rect.x + cannon->rect.width / 2,
                cannon->mousePos.y - cannon->rect.y + cannon->rect.height / 2
            ) * 2;

            cannon->angle = atan2f( 
                cannon->mousePos.y - ( cannon->rect.y + cannon->rect.height / 2 ),
                cannon->mousePos.x - ( cannon->rect.x + cannon->rect.width / 2 )
            );

        }

        if ( IsMouseButtonReleased( MOUSE_BUTTON_LEFT ) ) {
            cannon->preparing = false;
            cannon->fired = true;
            cannon->ball = createBall( 
                cannon->rect.x + cannon->rect.width / 2, 
                cannon->rect.y + cannon->rect.height / 2, 
                10, 
                RED,
                cannon->magnitude,
                cannon->angle
            );
        }

    }

    if ( cannon->ball != NULL ) {
        updateBall( cannon->ball, delta );
        if ( !cannon->ball->alive ) {
            destroyBall( cannon->ball );
            cannon->ball = NULL;
            cannon->preparing = false;
            cannon->fired = false;
        }
    }

}

void drawCannon( Cannon *cannon ) {

    DrawRectangleRec( cannon->rect, cannon->color );

    if ( cannon->preparing ) {

        DrawLineEx(
            (Vector2) {
                cannon->rect.x + cannon->rect.width / 2,
                cannon->rect.y + cannon->rect.height / 2
            },
            (Vector2) {
                cannon->mousePos.x,
                cannon->mousePos.y
            },
            2.0f,
            cannon->color
        );

        drawBallTrail( cannon );

    }

    if ( cannon->fired ) {
        drawBallTrail( cannon );
    }

    if ( cannon->ball != NULL ) {
        drawBall( cannon->ball );
    }

    DrawText( TextFormat( "magnitude: %.2f", cannon->magnitude ), 10, 10, 20, BLACK );
    DrawText( TextFormat( "angle: %.2f", RAD2DEG * cannon->angle ), 10, 30, 20, BLACK );

}

static void drawBallTrail( Cannon *cannon ) {

    Vector2 pos = {
        cannon->rect.x + cannon->rect.width / 2,
        cannon->rect.y + cannon->rect.height / 2
    };
    Vector2 prevPos = pos;
    
    Vector2 vel = (Vector2) { 
        cannon->magnitude * cosf( cannon->angle ),
        cannon->magnitude * sinf( cannon->angle )
    };

    float delta = GetFrameTime();

    for ( int i = 1; i < 300; i++ ) {

        pos.x += vel.x * delta;
        pos.y += vel.y * delta;
        vel.y += GRAVITY * delta;

        DrawLineV( prevPos, pos, GREEN );
        DrawCircleV( pos, 2, GREEN );

        prevPos = pos;
    }

}