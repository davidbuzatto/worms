#pragma once

#include <stdbool.h>
#include "raylib/raylib.h"

typedef struct Ball {

    Vector2 pos;
    Vector2 vel;
    float radius;
    Color color;

    float magnitude;
    float angle;
    bool alive;

} Ball;

typedef struct Cannon {

    Rectangle rect;
    Color color;

    Vector2 mousePos;
    bool preparing;
    bool fired;
    Ball *ball;

    float magnitude;
    float angle;

} Cannon;

typedef struct Building {
    Rectangle rect;
    Color color;
} Building;

typedef struct Explosion {
    Vector2 pos;
    float radius;
    Color color;
} Explosion;