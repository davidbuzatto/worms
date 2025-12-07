#include <stdlib.h>
#include <math.h>

#include "raylib/raylib.h"
#include "Types.h"
#include "Building.h"

void drawBuilding( Building *building ) {
    DrawRectangleRec( building->rect, building->color );
}