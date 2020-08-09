//  Everything GUI Related is in here!!
#include "main.h"
#include "gui.h"
#include "runcode.h"
#include "code.h"
#include "mouse.h"

// Need for sprites
#include "gfx/SCRSPT.h"
#include "decompress.h"
#include <compression.h>

int8_t ver_type = 1;
int8_t ver_maj = 1;
int8_t ver_min = 0;
fontlib_font_pack_t *my_font_pack;
fontlib_font_t *my_font;
ti_var_t file;
uint8_t error;
string_t *Ans_Data;
int newsprt_x = 186;
int checkDate = 0;
int iconX;

gfx_UninitedSprite(icon_buff, 70, 70);
gfx_UninitedSprite(GUI_buff, 170, 180);

void splash_screen(void){
	vars_int();
	gfx_FillScreen(0x5D);
	
	error = 0;
	for (i = 0; i < 5; i++){ // simple line 
		gfx_SetColor(0x3C);
		gfx_HorizLine(0, 213 + i, LCD_WIDTH);
	}
	gfx_SetTextFGColor(254);
	
	gfx_PrintStringXY("Loading..", 253, 225);
	
	//version
	show_ver();
	
	// By / Criedit 
	gfx_PrintStringXY("Alvajoy123", 1, 220);
	gfx_PrintStringXY("inspired by colorgram", 1, 230);
	
	// check if sprite files is valid
	file = ti_Open("SCRSPT","r");
	/*
	** Need to include Header to match same version of projram!!
	** to avoid issues
	** 
	*/
	if (!file){
		gfx_SetTextFGColor(224); // Index Red
		gfx_PrintStringXY("'SCRSPT' Sprite Appvar not found!", 1, 10);
		error = 3;
		return;
	}
	
	zx7_Decompress(GUI_buff, logo_compressed);
	gfx_SetTransparentColor(0xF0);
	gfx_TransparentSprite(GUI_buff, LCD_WIDTH / 2 - logo_width / 2, LCD_HEIGHT / 2 - logo_height / 2);
	
	gfx_Blit(1);
	
	gfx_SetTextFGColor(224); // Red
	
	ti_CloseAll();
	
	// Looks for font data
	file = ti_Open("SCRFONT", "r");
	my_font_pack = ti_GetDataPtr(file);
	
	if (!my_font_pack){ // Appvar was found
		gfx_PrintStringXY("'SCRFONT' Font Appvar not found!", 1, 10);
		error = 1;
		return;
	}
	
	ti_Close(file);
	
	my_font = fontlib_GetFontByIndexRaw(my_font_pack, 0);
	if (!my_font){ // 
		gfx_PrintStringXY("'SCRFONT' Font Appvar not invalid!", 1, 10);
		error = 2;
		return;
	}
	fontlib_SetFont(my_font, 0);
	
	// Ans Detection
	ti_RclVar(TI_STRING_TYPE, ti_Ans, &Ans_Data);
	
	if (!Ans_Data->data || Ans_Data == NULL){
		gfx_PopupMessage("Message:","Project name: 'SCRDATA'", 1, gfx_green);
		gfx_Blit(1);
		return;
	}else{
		gfx_SetTextXY(1, 10);
		proj.name = Ans_Data->data;
		gfx_PopupMessage("Project Name:", Ans_Data->data, 0, gfx_green);
		
		gfx_Blit(1);
	}
	
	wait(15); // Delay loading
	 
	return;
	
}

void show_ver(void){
	gfx_SetTextXY(1, 1);

	switch (ver_type){
		case 0:
			gfx_PrintString("pre a");
		break;
		
		case 1:
			gfx_PrintString("a v.");
		break;
		
		case 2:
			gfx_PrintString("b v.");
		break;
		
		case 3:
			gfx_PrintString("v.");
		break;
	}
	
	gfx_PrintInt(ver_maj, 1);
	gfx_PrintString(".");
	gfx_PrintInt(ver_min, 1);
}

void UI_setup(void){
	//bg color
	gfx_SetColor(0xFF);
	gfx_FillRectangle(0, 0, 320, 240);
	
	// header
	gfx_SetColor(0x5D);
	gfx_FillRectangle(0, 0, 320,31);
	gfx_SetColor(0x3C);
	gfx_HorizLine(0, 31, 320);
	
	// Box Setup
	gfx_SetTransparentColor(0xF0);
	
	// header
	zx7_Decompress(GUI_buff, small_logo_compressed);
	gfx_TransparentSprite(GUI_buff, 11, 5);
	
	zx7_Decompress(GUI_buff, share_load_compressed);
	gfx_TransparentSprite(GUI_buff, 104, 6);
	
	zx7_Decompress(GUI_buff, close_compressed);
	gfx_TransparentSprite(GUI_buff, 296, 7);
	
	// body
	zx7_Decompress(GUI_buff, command_box_compressed);
	gfx_TransparentSprite(GUI_buff, 3, 36);
	
	zx7_Decompress(GUI_buff, run_box_compressed);
	gfx_TransparentSprite(GUI_buff, 173, 36);
	
	zx7_Decompress(GUI_buff, code_box_compressed);
	gfx_TransparentSprite(GUI_buff, 3, 136);
	
	zx7_Decompress(GUI_buff, sprite_box_compressed);
	gfx_TransparentSprite(GUI_buff, 173, 179);
	
	free(GUI_buff);
	
	// version
	show_ver();
	
	// battery
	gfx_BatteryStatus();
	gfx_GetTime();
	gfx_GetDate();
	
	//if no code
	fontlib_SetForegroundColor(74);
	fontlib_SetCursorPosition(14, 158);
	fontlib_DrawString("click blocks above to build a script!");
	
	// show sprites in projram
	update_sprites_box();
	
	// display sprite
	canvas_update();
	
	for (n = 0; n < proj.spriteAmount; n++){
		sprite_update();
	}
	
	show_Blocks();
}

void gfx_GetTime(void){
	uint8_t sec = 0, min = 0, hur = 0;
	const char *time_ind[2] = {" AM", " PM"};
	
	boot_GetTime(&sec, &min, &hur);
	
	gfx_SetColor(0x5D);
	gfx_FillRectangle(222, 20, 42, 8);
	
	if (hur == 24){ // date update
		temp = 1;
		if (temp != checkDate){
			gfx_GetDate();
			checkDate = 1;
		}
	}else{
		temp = 0;
		checkDate = 0;
	}
	
	if (hur == 0) hur = 12;
	
	if (hur > 12) hur -= 12;
	
	fontlib_SetForegroundColor(255);
	fontlib_SetCursorPosition(222, 20);
	
	fontlib_DrawInt((unsigned int)hur, 2);
	fontlib_DrawString(" : ");
	fontlib_DrawInt((unsigned int)min, 2);
	fontlib_DrawString(time_ind[(uint8_t)boot_IsAfterNoon()]);
}

void gfx_GetDate(void){
	uint8_t day = 0, month = 0;
	uint16_t year;
	
	boot_GetDate(&day, &month, &year);
	
	gfx_SetColor(0x5D);
	gfx_FillRectangle(216, 8, 57, 8);
	
	fontlib_SetForegroundColor(255);
	fontlib_SetCursorPosition(216, 8);
	
	fontlib_DrawInt((unsigned int)month, 2);
	fontlib_DrawString("/");
	fontlib_DrawInt((unsigned int)day, 2);
	fontlib_DrawString("/");
	fontlib_DrawInt((unsigned int)year, 4);
}

void gfx_BatteryStatus(void){
	int X;
	temp = boot_GetBatteryStatus();
	gfx_SetColor(0);
	gfx_FillRectangle(285, 7, 4, 2);
	gfx_FillRectangle(283, 9, 8, 18);
	
	gfx_SetColor(255);
	gfx_FillRectangle(284, 9, 6, 17);
	
	if (temp > 1){
		gfx_SetColor(6); //light gren
	}else{
		gfx_SetColor(224);
	}
	
	if (temp > 3) gfx_FillRectangle(284 , 9, 6, 8);
	
	if (temp > 1) gfx_FillRectangle(284 , 15, 6, 6);
	
	if (temp >= 0) gfx_FillRectangle(284 , 21, 6, 5);
}

/*void gfx_load_box(void){
	load_box = gfx_MallocSprite(load_box_width,load_box_height);
	zx7_Decompress(load_box, load_box_compressed);
	
	Temp_Sprite = gfx_MallocSprite(load_box_width,load_box_height);
	gfx_GetSprite(Temp_Sprite, 80, 70);
	
	// gfx_TransparentSprite(load_box, LCD_WIDTH / 2 - load_box_width / 2, LCD_HEIGHT / 2 - load_box_height / 2);
	gfx_TransparentSprite(load_box, 80, 70);

	free(load_box);
	Display_Type = 1;
	wait(2);
}*/

void gfx_load_code(void){
	if (data[spriteN].codeX == 0) return;
	
	for (i = 0; i < 6; i++){
		codeBY = data[spriteN].code[i];
		data[spriteN].codeX = i;
		
		// Speed things up
		if (data[spriteN].code[i] == 0) goto code_load_done;
		
		// Looks
		if (codeBY < 16 && codeBY > 10) show_command = 1;
		// Hide
		if (codeBY < 24 && codeBY > 20) show_command = 2;
		// Rotate
		if (codeBY < 35 && codeBY > 30) show_command = 3;
		// Move
		if (codeBY < 45 && codeBY > 40) show_command = 4;
		 // Say
		if (codeBY < 56 && codeBY > 50) show_command = 5;
		
		// Displays Commands Based on show_command
		show_Blocks();
		
		if (codeBY % 10 == 1) gfx_CodeShow(1);	
		
		if (codeBY % 10 == 2) gfx_CodeShow(2);
		
		if (codeBY % 10 == 3) gfx_CodeShow(3);
		
		if (codeBY % 10 == 4) gfx_CodeShow(4);
		
		if (codeBY % 10 == 5) gfx_CodeShow(5);
		
	}
code_load_done:
	show_command = 1;
	// load_box_display_update();
	show_Blocks();
	return;
}

/*void gfx_costumes_box(void){
	sprite_box = gfx_MallocSprite(sprite_box_width, sprite_box_height);
	zx7_Decompress(sprite_box, sprite_box_compressed);
	
	Temp_Sprite = gfx_MallocSprite(load_box_width, load_box_height);
	gfx_GetSprite(Temp_Sprite, 80, 70);
	
	// gfx_TransparentSprite(sprites_box, LCD_WIDTH / 2 - sprites_box_width / 2, LCD_HEIGHT / 2 - sprites_box_height / 2);
	gfx_TransparentSprite(sprite_box, 80, 70);

	free(sprite_box);
	Display_Type = 2;
	wait(2);
}*/

void update_sprites_box(void){
	iconX = 184;
	sprite_box = gfx_MallocSprite(sprite_box_width, sprite_box_height);
	zx7_Decompress(sprite_box, sprite_box_compressed);
	gfx_TransparentSprite(sprite_box, 173, 179);
	free(sprite_box);
	
	for (i = 0; i < proj.spriteAmount; i++){
		if (i != spriteN){
			spriteicon_nul = gfx_MallocSprite(spriteicon_nul_width,spriteicon_nul_height);
			zx7_Decompress(spriteicon_nul, spriteicon_nul_compressed);
			gfx_TransparentSprite(spriteicon_nul, iconX, 186);
			free(spriteicon_nul);
		}else{
			spriteicon_sel = gfx_MallocSprite(spriteicon_sel_width, spriteicon_sel_height);
			zx7_Decompress(spriteicon_sel, spriteicon_sel_compressed);
			gfx_TransparentSprite(spriteicon_sel, iconX, 186);
			free(spriteicon_sel);			
		}
		get_Icon(i);
		iconX += spriteicon_nul_width + 10;
	}
	
	if (proj.spriteAmount != 3){
		newsprt_x = iconX;
		newsprt = gfx_MallocSprite(newsprt_width,newsprt_height);
		zx7_Decompress(newsprt, newsprt_compressed);
		gfx_TransparentSprite(newsprt, newsprt_x, 191);
		free(newsprt);
	}
	
	// Debug();
	gfx_SetTextFGColor(0);
}

void get_Icon(int pos){
	switch (costumes[pos].sprite){
		case 1:
			zx7_Decompress(icon_buff, cat_compressed);
		break;
		
		case 2:
			zx7_Decompress(icon_buff, dog_compressed);
		break;
		
		case 3:
			zx7_Decompress(icon_buff, fish_compressed);
		break;
		
		case 4:
			zx7_Decompress(icon_buff, frog_compressed);
		break;
		
		case 5:
			zx7_Decompress(icon_buff, clock_compressed);
		break;
		
		case 6:
			zx7_Decompress(icon_buff, shrek_compressed);
		break;
	}
	
	// if higher its from extern appvar. [Beta]
	
	Temp_Sprite = gfx_MallocSprite(31, 29);
	Temp_Sprite->width = 31;
	Temp_Sprite->height = 29;
	gfx_ScaleSprite(icon_buff, Temp_Sprite);
	gfx_TransparentSprite(Temp_Sprite, iconX + 2, 200);
	free(Temp_Sprite);
	return;
}

/*void load_box_display_update(void){
	switch (load_box_display){
		case 0:
			gfx_SetColor(0x5D);
			gfx_HorizLine(81, 80, 31);
			
			gfx_SetColor(0);
			gfx_HorizLine(114, 80, 31);
		break;
		
		case 1:
			gfx_SetColor(0);
			gfx_HorizLine(81, 80, 31);
			
			gfx_SetColor(0x5D);
			gfx_HorizLine(114, 80, 31);
		break;
		
	}
}*/


