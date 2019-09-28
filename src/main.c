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
        // Update Game
        updatephisycs();

        // Handle state, draw screen
        handlestate();

        // Handle controllers input
        handleinput();

        // Print Screen
        SPR_update();
        // Wait until next frame
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