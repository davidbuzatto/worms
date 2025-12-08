#include <stdlib.h>
#include <math.h>

#include "raylib/raylib.h"
#include "Types.h"
#include "Ball.h"
#include "GameWorld.h"

Ball *createBall( float x, float y, float radius, Color color, float magnitude, float angle ) {

    Ball *new = (Ball*) malloc( sizeof( Ball ) );

    new->pos = (Vector2) { x, y };
    new->vel = (Vector2) { 
        magnitude * cosf( angle ),
        magnitude * sinf( angle )
    };
    new->radius = radius;
    new->color = color;
    new->magnitude = magnitude;
    new->angle = angle;
    new->alive = true;

    return new;

}

void destroyBall( Ball *ball ) {
    free( ball );
}

void updateBall( Ball *ball, float delta ) {

    ball->pos.x += ball->vel.x * delta;
    ball->pos.y += ball->vel.y * delta;

    ball->vel.y += GRAVITY * delta;

    if ( ( ball->pos.x - ball->radius > GetScreenWidth() ) || ( ball->pos.x + ball->radius < 0 ) || ( ball->pos.y - ball->radius > GetScreenHeight() ) ) {
        ball->alive = false;
    }

}

void drawBall( Ball *ball ) {
    DrawCircleV( ball->pos, ball->radius, ball->color );
}