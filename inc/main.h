#include <genesis.h>
#include "game.h"


#ifndef MAIN_H
#define MAIN_H

#define SFX_FAIL 1

// Update the state of the game
void handlestate();
// update the phisycs
void updatephisycs();
//handle the input controls
void handleinput();

// Init game data
void init_game_data(struct game*);

// Run game stage
void run_stage(u16 current_stage, struct game *game);

void init_stage(u16 current_stage, struct game *game);

void inputHandler(u16,u16,u16);

void readcontrollers(struct game *game);

int check_collision(struct game *game);

#endif
