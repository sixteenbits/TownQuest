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
#include "sprt.h"




// main program
int main()
{
    // Game data
    struct game game;

    // Set screen width
    VDP_setScreenWidth320();

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
    int i;
	if(game->loaded_stage!=0 && game->current_stage==0) {
        game->loaded_stage=0;
        VDP_resetScreen();
        VDP_drawText("La Vara Estudios", 10 ,13);
        VDP_drawText("PRESENTS ...", 10 ,15);
    }
    if(game->loaded_stage!=1 && game->current_stage==1) {
        game->loaded_stage=1;
        VDP_resetScreen();
        VDP_drawText("Town Quest", 10 ,13);
    }

    if(game->loaded_stage!=2 && game->current_stage==2) {
        game->loaded_stage=2;
        VDP_resetScreen();
        //Indice para pdoer saber la carga
        u16 ind = TILE_USERINDEX;
        // Load tio de la vara sprite
        for(i=0; i<PLAYERS_SIZE; i++) {
        	game->players[i].player_sprite = SPR_addSprite(&tiovara, 15, 125, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE,ind));
        }
        run_stage(2, game);
    }

    // Change State
    if(game->current_stage==0 && game->frame > 400) {
        game->current_stage++;
    }
    else if(game->current_stage==1 && game->frame > 600) {
        game->current_stage++;
    }
}

void run_stage(u16 current_stage, struct game *game) {

    VDP_drawText("Fight!", 10 ,13);
}

void init_stage(u16 current_stage, struct game *game) {
	int i;
	for(i=0; i<ENEMY_SIZE; i++) {
		game->enemies[i].y = 0;
		game->enemies[i].x = 0;
		game->enemies[i].vy = -10;
		game->enemies[i].enabled = 1;
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

