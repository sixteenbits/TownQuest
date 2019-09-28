/**
 * TonwQuest main program.
 * Sixteen Bits.
 **/
#include <genesis.h>

#include "game.h"
#include "person.h"
#include "player.h"
#include "enemy.h"

// Update the state of the game
void handlestate();
// update the phisycs
void updatephisycs();
//handle the input controls
void handleinput();

struct game game;
// main program
int main()
{
    
    while(1)
    {

        handlestate();

        updatephisycs();
        handleinput();
        SPR_update();
        VDP_waitVSync();
    }
    return (0);
}

//hadle the game state
void handlestate(){
    game
}
// update the phisycs positions
void updatephisycs(){

}

// handle the input controllers
void handleinput(){

}