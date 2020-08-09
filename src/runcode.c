#include "runcode.h"

#include "gui.h"
#include "main.h"
#include "code.h"
#include "mouse.h"

// Need for sprites
#include "gfx/SCRSPT.h"
#include <compression.h>
#include "decompress.h"

struct costume_t costumes[3];
struct canvas_t stage;
int code_running = 0;
gfx_sprite_t *Ssprite;
gfx_sprite_t *costume_SPT;
int n; // temp
gfx_UninitedSprite(costume_buff, 70, 70);

// Proccessing code...
void runcode(void){
	gfx_SetTextFGColor(224);
	for (i = 0; i < 6; i++ ){
		kb_Scan();
		
		canvas_update();
		
		if (kb_IsDown(kb_Key2nd) && kb_IsDown(kb_KeyDel)){
			gfx_PrintStringXY("X", 174, 56);
			return;
		}
		
		for (n = 0; n < proj.spriteAmount; n++){
			kb_Scan();
			
			code_commands();
			sprite_update();
			say_commands();
			
			if (kb_IsDown(kb_Key2nd) && kb_IsDown(kb_KeyDel)){
				gfx_PrintStringXY("X", 174, 56);
				return;
			}
		
		}
		
		gfx_Blit(1);
		
		if (kb_IsDown(kb_Key2nd) && kb_IsDown(kb_KeyDel)){
			gfx_PrintStringXY("X", 174, 56);
			return;
		}
		
		delay(10);
	}
	return;
}

void code_commands(void){
	if (!costumes[n].active) return;
	codeBY = data[n].code[i];
	// if code is empty and is runned!!
	if (codeBY == 0 || codeBY > 50) return;
	
	// looks
	if (codeBY == 11){ // show 
		costumes[n].vis = 1;
		return;
	}
	if (codeBY == 12){ // hide 
		costumes[n].vis = 0;
		return;
	}
	if (codeBY == 13){ // reset size 
		if (costumes[n].s != 3) costumes[n].s = 1;
		return;
	}
	if (codeBY == 14){ // change size by 10
		if (costumes[n].s != 10) costumes[n].s++;
		return;
	}
	if (codeBY == 15){ // change size by -10
		if (costumes[n].s != 1) costumes[n].s--;
		return;
	}
	
	// contr. 
	if (codeBY == 21){ // wait 0.5 secs
		delay(500);
		return;
	}
	if (codeBY == 22){ // wait 1 secs
		delay(1000);
		return;
	}
	if (codeBY == 23){ // wait 3 secs
		delay(1500); // not really 3 secs :0
		return;
	}
	
	// rotate
	if (codeBY == 31){ // random pos
		costumes[n].x = randInt(176, 318 - costumes[n].width);
		costumes[n].y = randInt(56, 173 - costumes[n].height);
		if (costumes[n].y + costumes[n].height > 173){
			costumes[n].y -= costumes[n].height;
		}
		if (costumes[n].x + costumes[n].width > 315){
			costumes[n].x -= costumes[n].width;
		}
		return;
	}
	if (codeBY == 32){ // center of screen
		costumes[n].x = 246 - (costumes[n].width / 2);
		costumes[n].y = 117 - (costumes[n].height / 2);
		return;
	}
	if (codeBY == 33){ // turn right
		costumes[n].side = 1;
		return;
	}
	if (codeBY == 34){ // turn left 
		costumes[n].side = 0;
		return;
	}
	
	// move 
	if (codeBY == 41){ // right
		costumes[n].x += 10;
		if (costumes[n].x + costumes[n].width < 315){ 
			return;
		}else{ 
			costumes[n].x -= (costumes[n].x + costumes[n].width) - 315;
		}
		return;
	}	
	if (codeBY == 42){ // left
		costumes[n].x -= 10;
		if (costumes[n].x < 174){
			costumes[n].x += 174 - costumes[n].x;
		}
		return;
	}	
	if (codeBY == 43){ // up
		costumes[n].y -= 10;
		if (costumes[n].y < 56){
			costumes[n].y += 56 - costumes[n].y;
		}
		return;
	}
	if (codeBY == 44){ // down
		costumes[n].y += 10;
		if (costumes[n].y + costumes[n].height < 174){
			return;
		}else{ 
			costumes[n].y -= (costumes[n].y + costumes[n].height) - 174;
		}
		return;
	}
	
	return; 
}

/*void codeDebug(void){
	gfx_SetTextXY(175, 67);
	gfx_PrintString("spt.x:");
	gfx_PrintInt(costumes[n].x,3);
	
	gfx_SetTextXY(175, 77);
	gfx_PrintString("spt.y:");
	gfx_PrintInt(costumes[n].y,3);
	
	gfx_SetTextXY(175, 87);
	gfx_PrintString("Byte:");
	gfx_PrintInt(codeBY, 2);
}*/

void say_commands(void){
	// Bug say command display just a few seconds make say display longer
	if (!costumes[n].active) return;
	
	codeBY = data[n].code[i];
	if (codeBY < 51) return; 
	
	gfx_SetTextFGColor(0);
	gfx_SetTextBGColor(255);
	
	// say
	switch (codeBY){	
		case 51:
			gfx_PrintStringXY("hello", costumes[n].x, costumes[n].y);
			return;
		break;
		
		case 52:
			gfx_PrintStringXY("bye-bye", costumes[n].x, costumes[n].y);
			return;
		break;
		
		case 53:
			gfx_PrintStringXY("ouch", costumes[n].x, costumes[n].y);
			return;
		break;
		
		case 54:
			gfx_PrintStringXY("haha", costumes[n].x, costumes[n].y);
			return;
		break;
		
		case 55:
			gfx_PrintStringXY("hmm..", costumes[n].x, costumes[n].y);
			return;
		break;
	}
	return; 
}

void canvas_update(void){	
	// sets background
	switch (stage.bg){
		case 0:
		// clear bg
			gfx_SetColor(255);
			gfx_FillRectangle(174, 56, 142, 120); // 142x120 size of canvas
		break;
		
		case 1:
			// Decompress Stock BG
			bg = gfx_MallocSprite(bg02_width, bg02_height);
			zx7_Decompress(bg, bg02_compressed);
			gfx_TransparentSprite(bg, 174, 56);
			free(bg);
		break;
		
		case 2:
			bg = gfx_MallocSprite(bg03_width, bg03_height);
			zx7_Decompress(bg, bg03_compressed);
			gfx_TransparentSprite(bg, 174, 56);
			free(bg);
		break;
		
		case 3:
			bg = gfx_MallocSprite(bg04_width, bg04_height);
			zx7_Decompress(bg, bg03_compressed);
			gfx_TransparentSprite(bg, 174, 56);
			free(bg);
		break;
		
		case 4:
			bg = gfx_MallocSprite(bg05_width, bg05_height);
			zx7_Decompress(bg, bg05_compressed);
			gfx_TransparentSprite(bg, 174, 56);
			free(bg);
		break;
		
		case 5:
			bg = gfx_MallocSprite(bg06_width, bg06_height);
			zx7_Decompress(bg, bg06_compressed);
			gfx_TransparentSprite(bg, 174, 56);
			free(bg);
		break;
	}
	
	// if (stage.bg > 1){
		// return; // users can add more bgs later on
	// }
	return;
}

void sprite_update(void){
	// check if the sprite should be visable
	if (!costumes[n].active) return;
	
	if (costumes[n].vis != 0) {
		if (costumes[n].side == 1){ //turn left = 1 and right = 0
			load_sprites(n);
			Ssprite = gfx_MallocSprite(costumes[n].width, costumes[n].height);
			gfx_FlipSpriteY(costume_buff, Ssprite);
			
			costume_SPT = gfx_MallocSprite(costumes[n].width, costumes[n].height);
			costume_SPT->width = costumes[n].width;
			costume_SPT->height = costumes[n].height;
			gfx_ScaleSprite(Ssprite, costume_SPT);
			
			gfx_TransparentSprite(costume_SPT, costumes[n].x, costumes[n].y);
			
			free(Ssprite);
			free(costume_SPT);
		}else{
			load_sprites(n);
			costume_SPT = gfx_MallocSprite(costumes[n].width, costumes[n].height);
			costume_SPT->width = costumes[n].width;
			costume_SPT->height = costumes[n].height;
			gfx_ScaleSprite(costume_buff, costume_SPT);
			
			gfx_TransparentSprite(costume_SPT, costumes[n].x, costumes[n].y);
			free(costume_SPT);
		}
		
	}else{
		// Display nothing
	}
	// Debug();
	return;
}

void load_sprites(int pos){
	// stock sprites	
	switch (costumes[pos].sprite){
		case 1:
			costumes[pos].width = cat_width + costumes[pos].s;
			costumes[pos].height = cat_height + costumes[pos].s;
			zx7_Decompress(costume_buff, cat_compressed);
		break;
		
		case 2:
			costumes[pos].width = dog_width + costumes[pos].s;
			costumes[pos].height = dog_height + costumes[pos].s;
			zx7_Decompress(costume_buff, dog_compressed);
		break;
		
		case 3:
			costumes[pos].width = fish_width + costumes[pos].s;
			costumes[pos].height = fish_height + costumes[pos].s;
			zx7_Decompress(costume_buff, fish_compressed);
		break;
		
		case 4:
			costumes[pos].width = frog_width + costumes[pos].s;
			costumes[pos].height = frog_height + costumes[pos].s;
			zx7_Decompress(costume_buff, frog_compressed);
		break;
		
		case 5:
			costumes[pos].width = clock_width + costumes[pos].s;
			costumes[pos].height = clock_height + costumes[pos].s;
			zx7_Decompress(costume_buff, clock_compressed);
		break;
		
		case 6:
			costumes[pos].width = shrek_width + costumes[pos].s;
			costumes[pos].height = shrek_height + costumes[pos].s;
			zx7_Decompress(costume_buff, shrek_compressed);
		break;
		// if higher its from extern appvar. [Beta]
	}
	if (costumes[pos].height == NULL || costumes[pos].width == NULL) gfx_PopupMessage("Message: (error)","sprite Width or Height is equal to NULL", 0, gfx_red);
	return;
}