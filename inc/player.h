#include <genesis.h>


#ifndef PLAYER_H
#define PLAYER_H

#define ANIM_VARA 0
#define ANIM_RIGHT 1
#define ANIM_LEFT 2
#define ANIM_VICTORY 4
#define ANIM_IDLE 5

#define VARAZO_DURATION 15

struct player {
	// x position
	s16 x;
	// y position
	s16 y;
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
