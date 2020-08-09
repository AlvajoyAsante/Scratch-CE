// #include "defines.h"
#include "code.h"
#include <fontlibc.h>
#include "main.h"
#include "gui.h"
#include "runcode.h"

// Sprites
#include <compression.h>
#include "decompress.h"
#include "gfx/SCRSPT.h"


gfx_sprite_t *command_behind;
struct code_t data[3];
int codeBY;

void code_show(void){
	gfx_SetColor(255);
	gfx_FillRectangle(15, 160, 35, 61);
	
	gfx_SetTextXY(15, 158);
	gfx_PrintString("0: ");	
	gfx_PrintInt(data[spriteN].code[0], 2);
	
	gfx_SetTextXY(15, 168);
	gfx_PrintString("1: ");
	gfx_PrintInt(data[spriteN].code[1], 2);
	
	gfx_SetTextXY(15, 178);
	gfx_PrintString("2: ");
	gfx_PrintInt(data[spriteN].code[2], 2);
	
	gfx_SetTextXY(15, 188);
	gfx_PrintString("3: ");
	gfx_PrintInt(data[spriteN].code[3], 2);
	
	gfx_SetTextXY(15, 198);
	gfx_PrintString("4: ");
	gfx_PrintInt(data[spriteN].code[4], 2);
	
	gfx_SetTextXY(15, 208);
	gfx_PrintString("5: ");
	gfx_PrintInt(data[spriteN].code[5], 2);
	
	gfx_Blit(1);
	return;
}

void gfx_CodeShow(int selected){
	if (data[spriteN].codeX == 0) {
		gfx_SetColor(255);
		gfx_FillRectangle(14, 156, 146, 12);
	}
	
	command_behind = gfx_MallocSprite(120, 11);
	
	switch (selected){
		case 1:
			gfx_GetSprite(command_behind, 46, 49);
		break;
		
		case 2:
			gfx_GetSprite(command_behind, 46, 63);
		break;
		
		case 3:
			gfx_GetSprite(command_behind, 46, 78);
		break;
		
		case 4:
			gfx_GetSprite(command_behind, 46, 94);
		break;
		
		case 5:
			gfx_GetSprite(command_behind, 46, 109);
		break;
	}
	
	gfx_SetTransparentColor(0xFF);
	
	switch (data[spriteN].codeX){
		case 0:
			gfx_TransparentSprite(command_behind, 16, 156);
		break;
		
		case 1:
			gfx_TransparentSprite(command_behind, 16, 168);
		break;
		
		case 2:
			gfx_TransparentSprite(command_behind, 16, 180);
		break;
		
		case 3:
			gfx_TransparentSprite(command_behind, 16, 192);
		break;
		
		case 4:
			gfx_TransparentSprite(command_behind, 16, 204);
		break;
		
		case 5:
			gfx_TransparentSprite(command_behind, 16, 216);
		break;
	}
	
	free(command_behind);
	
	gfx_SetTransparentColor(0xF0);
	return;
}

void gfx_DeleteCode(void){
	gfx_SetColor(255);
	switch (data[spriteN].codeX){
		case 0:
			gfx_FillRectangle(14, 156, 146, 12);
			fontlib_SetForegroundColor(74);
			fontlib_SetCursorPosition(14, 158);
			fontlib_DrawString("click blocks above to build a script!");
		break;
		
		case 1:
			gfx_FillRectangle(15, 168, 121, 12);
		break;
		
		case 2:
			gfx_FillRectangle(15, 180, 121, 12);
		break;
		
		case 3:
			gfx_FillRectangle(15, 192, 121, 12);
		break;
		
		case 4:
			gfx_FillRectangle(15, 204, 121, 12);
		break;
		
		case 5:
			gfx_FillRectangle(15, 216, 121, 12);
		break;
	}
	return;
}

void gfx_ClearCodeBox(void){
	gfx_SetColor(255);
	for (i = 0; i < 6; i++){
		switch (i){
			case 0:
				gfx_FillRectangle(14, 156, 146, 12);
				fontlib_SetForegroundColor(74);
				fontlib_SetCursorPosition(14, 158);
				fontlib_DrawString("click blocks above to build a script!");
			break;
		
			case 1:
				gfx_FillRectangle(15, 168, 121, 12);
			break;
		
			case 2:
				gfx_FillRectangle(15, 180, 121, 12);
			break;
		
			case 3:
				gfx_FillRectangle(15, 192, 121, 12);
			break;
		
			case 4:
				gfx_FillRectangle(15, 204, 121, 12);
			break;
		
			case 5:
				gfx_FillRectangle(15, 216, 121, 12);
			break;
		}
	}
}

void costume_Delete(int pos){
	if (pos != 2){
		if (costumes[pos + 1].active == 1){
			if (pos == spriteN && pos != 0){
				spriteN--;
			}else if (pos == 0){
				spriteN = 0;
			}
			costumes[pos] = costumes[pos + 1];
			costumes[pos + 1].active = 0;
			Delete_AllCode(pos + 1);
			if (pos + 2 == 2){
				if (costumes[pos + 2].active == 1){
					costumes[pos + 1] = costumes[pos + 2];
					costumes[pos + 2].active = 0;
					Delete_AllCode(pos + 2);
				}
			}	
		}else{
			if (pos == spriteN) spriteN--;
			costumes[pos].active = 0;
			Delete_AllCode(pos);
		}
	}else{
		if (pos == spriteN) spriteN--;
		costumes[pos].active = 0;
		Delete_AllCode(pos);
	}
	
	proj.spriteAmount--;
	
	canvas_update();
	for (n = 0; n < proj.spriteAmount; n++){
			sprite_update();
	}
	
	update_sprites_box();
	gfx_ClearCodeBox();
	gfx_load_code();
}

void Delete_AllCode(int pos){
	data[pos].codeX = 0;
	for (i = 0; i < data[pos].codeX; i++){
		data[pos].code[i] = 0;
	}
}