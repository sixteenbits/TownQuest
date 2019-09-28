#include <genesis.h>
#include "game.h"


#ifndef MAIN_H
#define MAIN_H

// Update the state of the game
void handlestate();
// update the phisycs
void updatephisycs();
//handle the input controls
void handleinput();

// Init game data
void init_game_data(struct game*);

#endif