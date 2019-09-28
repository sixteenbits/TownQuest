#include <genesis.h>


#ifndef PERSON_H
#define PERSON_H

struct person {
    // x position
    u16 x;
    // y position
    u16 y;
    // Person Sprite
    Sprite* person_sprite;
    // Enemy active
    bool enabled;
};

#endif