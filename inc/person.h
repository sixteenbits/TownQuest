#include <genesis.h>


#ifndef PERSON_H
#define PERSON_H

struct person {
    // x position
    s16 x;
    // y position
    s16 y;
    // vertical speed
    s16 vy;
    // Person Sprite
    Sprite* person_sprite;
    // Enemy active
    bool enabled;
    // Enemy index
    u16 index;
};

#endif
