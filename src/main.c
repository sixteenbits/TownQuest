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




// main program
int main()
{
    // Game data
    struct game game;

    //Init sprite engine
    SPR_init(0, 0, 0);
    
    // Init game data
    init_game_data(&game);

    while(1)
    {
        // Update frame counter
        game.frame++;
        // Update Game
        updatephisycs();

        // Handle state, draw screen
        handlestate(&game);

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
void handlestate(struct game *game){
    if(game->current_stage==0) {
        VDP_drawText("La Vara Estudios", 10 ,13);
        VDP_drawText("PRESENTS ...", 10 ,15);
    }
    if(game->current_stage==1) {
        VDP_drawText("Town Quest", 10 ,13);
    }

    if(game->current_stage==2) {
        VDP_drawText("First round!", 10 ,13);
    }

    // Change State
    if(game->current_stage==0 && game->frame > 100) {
        game->current_stage++;
    }
    else if(game->current_stage==1 && game->frame > 200) {
        game->current_stage++;
    }
}
// update the phisycs positions
void updatephisycs(){

}

// handle the input controllers
void handleinput(){

}

void init_game_data(struct game *game){
    game->background=NULL;
    game->current_stage=0;
    game->loaded_stage=-1;
}

