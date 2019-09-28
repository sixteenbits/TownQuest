#include <genesis.h>
#include "player.h"
#include "enemy.h"
#include "person.h"


#ifndef GAME_H
#define GAME_H

#define PLAYERS_SIZE 1
#define ENEMY_SIZE 10
#define PERSON_SIZE 10
#define SCREEN_HEIGHT 224

struct game {
    // Backgrounds
    Image* background;
    // Players
    struct player players[PLAYERS_SIZE];
    // Enemies
    struct enemy enemies[ENEMY_SIZE];
    // Person
    struct person person[ENEMY_SIZE];
    // Stage to display
    u16 current_stage;
    // Loaded Stage
    u16 loaded_stage;
    // Clock. Current frame number
    u16 frame;
    // Flag game over
    int game_over;
};

#endif
