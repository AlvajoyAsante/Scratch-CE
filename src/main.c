/////////////////////////////
// Scratch by Alvajoy      //
//                         //
// orginal project from    //
// sratch ID : colorgram   //
/////////////////////////////
// Keep these headers
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

// Standard headers
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Graphic libs
#include <graphx.h>
#include <keypadc.h>
#include <fileioc.h>
#include <compression.h>
#include <fontlibc.h>

// my headers
#include "main.h"
#include "mouse.h"
#include "gui.h"
#include "runcode.h"
#include "decompress.h"
#include "gfx/SCRSPT.h"
#include "code.h"
#include "files.h"


// Variables
int i;
int temp;
char *Temp_Char;
struct vars_t proj;
int spriteN = 0;

// ****NTS: implement delay..
void main(void){
	SCRSPT_init(); // Setup Sprites
	
	// font setup
	fontlib_SetWindowFullScreen();
    fontlib_SetTransparency(true);
	fontlib_SetLineSpacing(1, 1);
    fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);
	
	gfx_Begin();
	gfx_SetDraw(1);
	gfx_SetTextFGColor(0);
	
	splash_screen();
	load_data();
	
	// if there was no error from splash run below else exit
	if (!error){
		gfx_SetTextFGColor(0);
		UI_setup();
		gfx_load_code();
		gfx_PopupMessage("Quick Update:  ","Alpha v 1.0 : 'Port' Released!", 0, gfx_yellow);
		display_mouse(); // mouse loop!!
	}
	
	if (error > 0){
		gfx_Blit(1);
		while(!os_GetCSC());
	}else{
		data_save();
	}
	
	// gfx_Blit(1);
	// free(costume_buff);
	// free(icon_buff);
	// free(GUI_buff);
	
	gfx_End();
	os_ClrHomeFull();
} 


// routines below!!
void vars_int(void){
	// Stage Setup
	stage.bg = 0;
	stage.mxbg = 5;
	
	// check sprites amount
	if (proj.spriteAmount == 0){	
		proj.spriteAmount++;
		costumes[proj.spriteAmount - 1].sprite = 1;
	}
	// sprites (demo) var
	Set_Costumes_Data();
}

void Set_Costumes_Data(void){
	for (i = 0; i < proj.spriteAmount; i++){
		if (costumes[i].active != 1){
			costumes[i].active = 1;
			costumes[i].vis = 1;
			costumes[i].r = 0;
			costumes[i].s = -5;
			costumes[i].x = 223;
			costumes[i].y = 79;
			costumes[i].side = 0;
		}
	}
}
	
/*void Debug(void){
	gfx_SetColor(0xFF);
	gfx_FillRectangle(279,0, 320 - 279, 32);
	
	gfx_SetTextXY(280, 0);
	gfx_PrintString("Sn: ");	
	gfx_PrintInt(show_command_old, 2);
	
	gfx_SetTextXY(280, 10);
	gfx_PrintString("w ");	
	gfx_PrintInt(costumes[0].width, 2);
	
	gfx_SetTextXY(280, 20);
	gfx_PrintString("h:");	
	gfx_PrintInt(costumes[0].height, 2);
	
	gfx_Blit(1);
	return;
}*/

void wait(const int amount){
	temp = 0;
	while (temp != amount){
		temp += 1;
		gfx_Blit(1);
	}
	return;
}

void gfx_PopupMessage(const char *header, const char *message, int type, int color){
	int x, y, h, w;
	w = fontlib_GetStringWidth(message) + fontlib_GetStringWidth(header);
	if (w > 250) w = 250;
	h = w / 3;
	if (h < 41) h = 50;
	x = 160 - w / 2;
	y = 120 - h / 2;
	
	Temp_Sprite = gfx_MallocSprite(w, h);
	gfx_GetSprite(Temp_Sprite, x, y);
	
	gfx_SetColor(0);
	gfx_FillRectangle(x, y, w, h);
	gfx_SetColor(color);
	gfx_Rectangle(x, y, w, h);
	gfx_Rectangle(x + 1, y + 1, w - 2, h - 2);
	
	fontlib_SetWindow(x + 3, y + 3, w - 6, h - 6);
	fontlib_HomeUp();
	fontlib_SetForegroundColor(255);
	fontlib_DrawString(header);
	fontlib_Newline();
	fontlib_DrawString(message);
	fontlib_Newline();
	
	gfx_Blit(1);
	
	switch (type){
		case 0:
			fontlib_DrawString("Press any key.");
			gfx_Blit(1);
			while(!os_GetCSC());
		break;
		
		case 1:
			wait(10);
		break;
	}
	
	wait(10);
	
	gfx_Sprite(Temp_Sprite, x, y);
	free(Temp_Sprite);
	fontlib_SetWindowFullScreen();
	return;
}