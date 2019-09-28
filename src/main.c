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
#include "gfx.h"


struct game *global_game;

// main program
int main()
{
    // Game data
    struct game game;
    global_game = &game;

    // Set screen width
    VDP_setScreenWidth320();

    //Init sprite engine
    SPR_init(0, 0, 0);
    
    // Init Controls
    JOY_init();
    JOY_setEventHandler(&inputHandler);

    // Init game data
    init_game_data(&game);

    while(1)
    {
        // Update frame counter
        game.frame++;

        readcontrollers(&game);

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
        u16 ind=TILE_USERINDEX;
        VDP_setPaletteColors(PAL0, (u16*)titulo.palette->data, 16);
        VDP_drawImageEx(PLAN_A, &titulo, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
        VDP_drawText("Town Quest", 3 ,5);
    }

    if(game->loaded_stage!=2 && game->current_stage==2) {
        game->loaded_stage=2;
        init_stage(game->loaded_stage, game);
        VDP_resetScreen();
        //Indice para pdoer saber la carga
        u16 ind = TILE_USERINDEX;
        // Load tio de la vara sprite
        for(i=0; i<PLAYERS_SIZE; i++) {
        	game->players[i].player_sprite = SPR_addSprite(&tiovara, game->players[i].x, game->players[i].y, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE,ind++));
        }
        VDP_setPalette(PAL1,tiovara.palette->data);
        for(i=0; i<PLAYERS_SIZE; i++) {
        	SPR_setAnim(game->players[i].player_sprite,ANIM_IDLE);
        }
    }
    if(game->loaded_stage>=2 && game->loaded_stage==game->current_stage) {
        run_stage(game->loaded_stage, game);
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
	int i;
	for(i=0; i<PLAYERS_SIZE; i++) {
		if(game->players[i].end_varazo_frame && game->frame > game->players[i].end_varazo_frame) {
			SPR_setAnim(game->players[i].player_sprite,ANIM_IDLE);
			game->players[i].end_varazo_frame=0;
		}
	}
    VDP_drawText("Fight!", 10 ,13);
}

void init_stage(u16 current_stage, struct game *game) {
	int i;
	for(i=0; i<PLAYERS_SIZE; i++) {
		game->players[i].y = 160;
		game->players[i].x = 150;
    	game->players[i].end_varazo_frame=0;
	}
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

void inputHandler(u16 joy, u16 state, u16 changed)
{
	if (state & BUTTON_A) {
		SPR_setAnim(global_game->players[joy].player_sprite,ANIM_VARA);
		global_game->players[joy].end_varazo_frame = global_game->frame+VARAZO_DURATION;
    }
}

void readcontrollers(struct game *game)
{
	int i;
	int value[2];
    //Se lee el estado del joistick en el puerto 1
    value[0] = JOY_readJoypad(JOY_1);
    value[1] = JOY_readJoypad(JOY_2);

    for(i=0; i<PLAYERS_SIZE; i++) {
		if(value[i] & BUTTON_RIGHT){
			game->players[i].x++;
			SPR_setPosition(game->players[i].player_sprite, game->players[i].x, game->players[i].y);
			SPR_setAnim(game->players[i].player_sprite,ANIM_RIGHT);
		}

		if(value[i] & BUTTON_LEFT){
			game->players[i].x--;
			SPR_setPosition(game->players[i].player_sprite, game->players[i].x, game->players[i].y);
			SPR_setAnim(game->players[i].player_sprite,ANIM_LEFT);
		}
    }
}

