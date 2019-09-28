/**
 * TonwQuest main program.
 * Sixteen Bits.
 **/
#include <genesis.h>

#include "game.h"
#include "person.h"
#include "player.h"
#include "enemy.h"
#include "main.h"



struct game game;
// main program
int main()
{
    //Inicializa motor de sprites con los parámetros por defecto
    SPR_init(0, 0, 0);
    
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
    VDP_drawText("Hello Town Quest", 10 ,13);
}
// update the phisycs positions
void updatephisycs(){

}

// handle the input controllers
void handleinput(){

}