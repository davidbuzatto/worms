/**
 * @file ResourceManager.c
 * @author Prof. Dr. David Buzatto
 * @brief ResourceManager implementation.
 * 
 * @copyright Copyright (c) 2025
 */
#include <stdio.h>
#include <stdlib.h>

#include "ResourceManager.h"
#include "raylib/raylib.h"

ResourceManager rm = { 0 };

void loadResourcesResourceManager( void ) {
    //rm.background = LoadTexture( "resources/images/background.png" );
    //rm.soundExample = LoadSound( "resources/sfx/powerUp.wav" );
    //rm.musicExample = LoadMusicStream( "resources/musics/overworld1.ogg" );
}

void unloadResourcesResourceManager( void ) {
    //UnloadTexture( rm.background );
    //UnloadSound( rm.soundExample );
    //UnloadMusicStream( rm.musicExample );
}