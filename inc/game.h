#include <genesis.h>


#ifndef GAME_H
#define GAME_H

#define PLAYERS_SIZE 1
#define ENEMY_SIZE 10
#define PERSON_SIZE 10

struct game {
    // Players
    struct player players[PLAYERS_SIZE];
    // Enemies
    struct enemy enemies[ENEMY_SIZE];
    // Person
    struct person person[ENEMY_SIZE];
};

#endif