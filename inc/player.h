#include <genesis.h>


#ifndef PLAYER_H
#define PLAYER_H

#define VARAZO_DURATION 15

struct player {
    // Player remaining lifes
    u8 lifes;
    // Current Player Score
    u16 score;
    // Player Sprite
    Sprite* player_sprite;
    // Saves the frame where varazo finish
    u16 end_varazo_frame;
};

#endif
