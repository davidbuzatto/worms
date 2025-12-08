#pragma once

#include "raylib/raylib.h"
#include "GameWorld.h"
#include "Types.h"

Cannon *createCannon( float x, float y, float width, float height, float angle, Color color );
void destroyCannon( Cannon *cannon );
void updateCannon( Cannon *cannon, float delta, GameWorld *gw );
void drawCannon( Cannon *cannon );