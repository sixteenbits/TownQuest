#include <genesis.h>


#ifndef ENEMY_H
#define ENEMY_H

struct enemy {
    // x position
    s16 x;
    // y position
    s16 y;
    // vy
    s16 vy;
    // Player Sprite
    Sprite* enemy_sprite;
    // Enemy active
    bool enabled;
};

#endif