#pragma once

#include "raylib/raylib.h"
#include "Types.h"

Ball *createBall( float x, float y, float radius, Color color, float magnitude, float angle );
void destroyBall( Ball *ball );
void updateBall( Ball *ball, float delta );
void drawBall( Ball *ball );