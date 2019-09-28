#include <genesis.h>


#ifndef PLAYER_H
#define PLAYER_H

struct player {
    // Player remaining lifes
    u8 lifes;
    // Current Player Score
    u16 score;
    // Player Sprite
    Sprite* player_sprite;
};

#endif