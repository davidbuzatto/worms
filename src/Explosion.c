#include <stdlib.h>
#include <math.h>

#include "raylib/raylib.h"
#include "Types.h"
#include "Explosion.h"

void drawExplosion( Explosion *explosion ) {
    DrawCircleV( explosion->pos, explosion->radius, explosion->color );
}