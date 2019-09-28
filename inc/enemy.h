#include <genesis.h>


#ifndef ENEMY_H
#define ENEMY_H

struct enemy {
    // x position
    u16 x;
    // y position
    u16 y;
    // Player Sprite
    Sprite* enemy_sprite;
    // Enemy active
    bool enabled;
};

#endif