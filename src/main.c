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
#include "sfx.h"


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
	if(game->loaded_stage!=10 && game->current_stage==10) {
		game->loaded_stage=10;
		VDP_resetScreen();
		u16 ind=TILE_USERINDEX;
		VDP_setPaletteColors(PAL0, (u16*)game_over.palette->data, 16);
		VDP_drawImageEx(PLAN_A, &game_over, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
		return;
	}
	if(game->loaded_stage!=0 && game->current_stage==0) {
        game->loaded_stage=0;
        VDP_resetScreen();
        u16 ind=TILE_USERINDEX;
        VDP_setPaletteColors(PAL0, (u16*)vara.palette->data, 16);
        VDP_drawImageEx(PLAN_A, &vara, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    }
    if(game->loaded_stage!=1 && game->current_stage==1) {
        game->loaded_stage=1;
        VDP_resetScreen();
        u16 ind=TILE_USERINDEX;
        VDP_setPaletteColors(PAL0, (u16*)titulo.palette->data, 16);
        VDP_drawImageEx(PLAN_A, &titulo, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    }

    if(game->loaded_stage!=2 && game->loaded_stage<10 && game->current_stage==2) {
        game->loaded_stage=2;
        init_stage(game->loaded_stage, game);
    }
    if(game->loaded_stage>=2 && game->loaded_stage<10 && game->loaded_stage==game->current_stage) {
        run_stage(game->loaded_stage, game);
    }

    // Change State
    if(game->current_stage==0 && game->frame > 400) {
        game->current_stage++;
    }
    else if(game->current_stage==1 && game->frame > 600) {
        game->current_stage++;
    }
    else if(game->game_over && game->loaded_stage!=10) {
    	game->current_stage=10;
    }
}

void run_stage(u16 current_stage, struct game *game) {
	int i;
	for(i=0; i<PLAYERS_SIZE; i++) {
		// Varazo ends
		if(game->players[i].end_varazo_frame && game->frame > game->players[i].end_varazo_frame) {
			SPR_setAnim(game->players[i].player_sprite,ANIM_IDLE);
			game->players[i].end_varazo_frame=0;
		}
		if(game->players[i].lifes<=0) {
			//game->game_over=1;
		}
	}
	for(i=0; i<ENEMY_SIZE; i++) {
		// Update enemy position
		game->enemies[i].y+=game->enemies[i].vy;
		// If out of screen, reset position
		if(game->enemies[i].y>SCREEN_HEIGHT) {
			// remove sprite
			SPR_releaseSprite(game->enemies[i].enemy_sprite);
			game->enemies[i].enemy_sprite=NULL;
			game->enemies[i].enabled=0;
		}
		else {
			SPR_setPosition(game->enemies[i].enemy_sprite, game->enemies[i].x, game->enemies[i].y);

			// Varazo ends
			if(game->enemies[i].end_transform && game->frame > game->enemies[i].end_transform) {
				SPR_setAnim(game->enemies[i].enemy_sprite,TRANSFORMED_SPRITE);
				game->enemies[i].end_transform=0;
			}
		}
	}

	// Update persons
	for(i=0; i<PERSON_SIZE; i++) {
		game->person[i].y+=game->person[i].vy;
		// If out of screen, remove
		if(game->person[i].y>SCREEN_HEIGHT) {
			game->person[i].enabled=0;
			SPR_releaseSprite(game->person[i].person_sprite);
			game->person[i].person_sprite=NULL;
		}
		else {
			SPR_setPosition(game->person[i].person_sprite, game->person[i].x, game->person[i].y);
		}
	}
}

void init_stage(u16 current_stage, struct game *game) {
	int i;
	int positions_s2[3]={50,150,240};

	game->game_over=0;
    for(i=0; i<PLAYERS_SIZE; i++) {
		game->players[i].y = 160;
		game->players[i].x = 150;
    	game->players[i].end_varazo_frame=0;
    	game->players[i].lifes=INITIAL_LIFES;
	}
	for(i=0; i<ENEMY_SIZE; i++) {
		game->enemies[i].y = -1*random()%500;
		game->enemies[i].x = random()%300;
		game->enemies[i].vy = 1;
		game->enemies[i].enabled = 1;
		game->enemies[i].end_transform = 0;
	}

	for(i=0; i<PERSON_SIZE; i++) {
		game->person[i].y = -1*random()%500;
		game->person[i].x = random()%300;
		game->person[i].vy = 1;
		game->person[i].enabled = 1;
	}

	if(current_stage == 2) {
		for(i=0; i<ENEMY_SIZE; i++) {
			game->enemies[i].x = positions_s2[random()%3];
		}
		for(i=0; i<PERSON_SIZE; i++) {
			game->person[i].x = positions_s2[random()%3];
		}
	}

	VDP_resetScreen();
	//Indice para pdoer saber la carga
	u16 ind = TILE_USERINDEX;
     SYS_disableInts();
    //init sounds
    SND_setPCM_XGM(SFX_FAIL, fallo, sizeof(fallo));
    //init music
   
    XGM_startPlay(fondo1);
    
    SYS_enableInts();

    // Load Background
    VDP_setPaletteColors(PAL0, (u16*)stage1.palette->data, 16);
    VDP_drawImageEx(PLAN_A, &stage1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);

    // Load tio de la vara sprite
    for(i=0; i<PLAYERS_SIZE; i++) {
    	game->players[i].player_sprite = SPR_addSprite(&tiovara, game->players[i].x, game->players[i].y, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE,ind++));
    }
    for(i=0; i<ENEMY_SIZE; i++) {
    	game->enemies[i].enemy_sprite = SPR_addSprite(&gente, game->enemies[i].x, game->enemies[i].y, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE,ind++));
    	game->enemies[i].index=2*(random()%3);
    	SPR_setAnim(game->enemies[i].enemy_sprite,game->enemies[i].index);
    }
    for(i=0; i<PERSON_SIZE; i++) {
    	game->person[i].person_sprite = SPR_addSprite(&gente, game->person[i].x, game->person[i].y, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE,ind++));
    	game->person[i].index=6+(2*(random()%2));
    	SPR_setAnim(game->person[i].person_sprite,game->person[i].index);
    }
    game->lifes=SPR_addSprite(&vararota, 10, 180, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE,ind++));
    VDP_setPalette(PAL1,tiovara.palette->data);
    VDP_setPalette(PAL2,gente.palette->data);
    VDP_setPalette(PAL3,vararota.palette->data);
    for(i=0; i<PLAYERS_SIZE; i++) {
    	SPR_setAnim(game->players[i].player_sprite,ANIM_IDLE);
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
    game->game_over=0;
}

void inputHandler(u16 joy, u16 state, u16 changed)
{
	if(global_game->game_over) {
		return;
	}
	if (state & (BUTTON_A | BUTTON_B | BUTTON_C)) {
		SPR_setAnim(global_game->players[joy].player_sprite,ANIM_VARA);
		global_game->players[joy].end_varazo_frame = global_game->frame+VARAZO_DURATION;
		if(check_collision(global_game)) {
			// Play HIT sound
		}
		else {
			// Play EMPTY sound
            XGM_startPlayPCM(SFX_FAIL, 1, SOUND_PCM_CH1);
		}
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
		else if(value[i] & BUTTON_LEFT){
			game->players[i].x--;
			SPR_setPosition(game->players[i].player_sprite, game->players[i].x, game->players[i].y);
			SPR_setAnim(game->players[i].player_sprite,ANIM_LEFT);
		}
		else if(!game->players[i].end_varazo_frame) {
			SPR_setAnim(game->players[i].player_sprite,ANIM_IDLE);
		}
    }
}

int check_collision(struct game *game){
	int i, j, sprite;
	for(i=0; i<PLAYERS_SIZE; i++) {
		for(j=0; j<ENEMY_SIZE; j++) {
			if(game->enemies[j].enabled
						&& abs(game->players[i].x-game->enemies[j].x) < 30
						&& abs(game->players[i].y-game->enemies[j].y) < 30) {
				game->enemies[j].enabled=0;
				SPR_setAnim(game->enemies[j].enemy_sprite,game->enemies[j].index+1);
				game->enemies[j].end_transform=game->frame+TRANSFORMATION_DURATION;
				return 1;
			}
		}

		for(j=0; j<PERSON_SIZE; j++) {
			if(game->person[j].enabled
					&& abs(game->players[i].x-game->person[j].x) < 20
					&& abs(game->players[i].y-game->person[j].y) < 20) {
				SPR_setAnim(game->players[i].player_sprite, ANIM_FAIL);
				SPR_setAnim(game->person[j].person_sprite,game->person[j].index+1);
				game->players[i].lifes--;
				sprite = INITIAL_LIFES-game->players[i].lifes;
				if(sprite>2) {
					sprite=2;
				}
				SPR_setAnim(game->lifes, sprite);
				return 1;
			}
		}
	}

	return 0;
}

