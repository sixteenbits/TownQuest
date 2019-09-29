#include <genesis.h>


#ifndef PLAYER_H
#define PLAYER_H

#define ANIM_VARA 0
#define ANIM_RIGHT 1
#define ANIM_LEFT 2
#define ANIM_FAIL 3
#define ANIM_VICTORY 4
#define ANIM_IDLE 5

#define VARAZO_DURATION 15
#define INITIAL_LIFES 3
#define GRACE_PERIOD 30

struct player {
	// x position
	s16 x;
	// y position
	s16 y;
	// Player remaining lifes
    s16 lifes;
    // Current Player Score
    u16 score;
    // Player Sprite
    Sprite* player_sprite;
    // Saves the frame where varazo finish
    u16 end_varazo_frame;
    // Grace period after collision
    u16 life_grace;
};

#endif
