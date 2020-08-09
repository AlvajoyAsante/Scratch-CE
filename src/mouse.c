// everthing mouse related is in here!!
// #include "defines.h"
#include "runcode.h"
#include "mouse.h"
#include "gui.h"
#include "code.h"
#include "main.h"
#include "files.h"

// Needed for sprites
#include <compression.h>
#include "decompress.h"
#include "gfx/SCRSPT.h"


int mouseX = LCD_WIDTH / 2;
int mouseY = LCD_HEIGHT / 2;
int mouseSP = 4;
int show_command = 1;
int ext = 0;
kb_key_t key;
gfx_sprite_t *behind_sprite;
int timerX = 0;
// int load_box_display = 1;
/*
* check whats on display via mouse enter
* Display_Type = 0; "Main UI on screen"
* Display_Type = 1 or 2; "load / sprite box on screen"
*/
// uint8_t Display_Type = 0;

void display_mouse(void){
	// Copies Sprite BG to behind sprite
	gfx_SetTransparentColor(0xF0);
	behind_sprite = gfx_MallocSprite(17, 22);
	gfx_GetSprite(behind_sprite, mouseX, mouseY);
	
	while (kb_Data[6] != kb_Clear && ext != 1){
		kb_Scan();
		key = kb_Data[7];

		gfx_Sprite(behind_sprite, mouseX, mouseY);
		
		other_keys();
		
		gfx_GetTime();
		
		if (timerX == 30000) gfx_BatteryStatus(); 
		
		mouse_keys();
		
		gfx_GetSprite(behind_sprite, mouseX, mouseY); // gets new mouse pos behind_sprite
		Render_Mouse();

		gfx_Blit(1);
		timerX += 1;		
	} 
	// free allocated data
	free(behind_sprite);
	return;
}

void mouse_Enter(void){
// too long redo later on :(
	/*
	if (Display_Type > 0){
		switch (Display_Type){
			case 1:
			mouseEnter_load();
			break;
				
			case 2:
			mouseEnter_sprites();
			break;
		}
		return;
	}*/
	
	// share 
	if (mouseX > 104 && mouseX < 143 && mouseY > 6 && mouseY < 27){
		// gfx_PrintStringXY("X", 104, 6);	
		// share_data();
		gfx_PopupMessage("Message: ","No proper use for this yet.", 0, gfx_orange);
		return;
	}
	
	// load
	if (mouseX > 155 && mouseX < 197 && mouseY > 6 && mouseY < 27){
		// gfx_load_box();
		gfx_PopupMessage("Message: ","Set Ans to project name to load.", 0, gfx_orange);
		return;
	}
	
	// close (X)
	if (mouseX > 296 && mouseX < 316 && mouseY > 7 && mouseY < 27){
		ext = 1;
		return;
	}
	
	// bg left 179, 40
	if (mouseX > 179 && mouseX < 187 && mouseY > 40 && mouseY < 52){
		if (stage.bg != 0){
			stage.bg -= 1;
			canvas_update();
			for (n = 0; n < proj.spriteAmount; n++){
				sprite_update();
			}
		}
		return;
	}
	
	// bg right 216, 40
	if (mouseX > 216 && mouseX < 224 && mouseY > 40 && mouseY < 52){
		if (stage.bg != stage.mxbg){
			stage.bg += 1;
			canvas_update();
			for (n = 0; n < proj.spriteAmount; n++){
				sprite_update();
			}
		}
		return;
	}
	
	// add bg 194, 39
	if (mouseX > 194 && mouseX < 209 && mouseY > 39 && mouseY < 52){
		// gfx_costumes_box();
		gfx_PopupMessage("Message: ","No proper use for this yet.", 0, gfx_orange);
		return;
	}
	
	// run 280,39
	if (mouseX > 280 && mouseX < 292 && mouseY > 39 && mouseY < 52){
		wait(2);
		runcode();
		return;
	}
	
	// stop 301, 39
	if (mouseX > 301 && mouseX < 314 && mouseY > 39 && mouseY < 52){
		// gfx_PrintStringXY("*", 301, 39);
		canvas_update();
		for (n = 0; n < proj.spriteAmount; n++){
			sprite_update();
		}
		return;
	}
	
	// looks 7,45
	if (mouseX > 7 && mouseX < 36 && mouseY > 45 && mouseY < 57){
		show_command = 1;
		show_Blocks();
		return;
	}
	
	// contr 7,59
	if (mouseX > 7 && mouseX < 36 && mouseY > 59 && mouseY < 71){
		show_command = 2;
		show_Blocks();
		return;
	}
	
	// rotate 7,72
	if (mouseX > 7 && mouseX < 36 && mouseY > 72 && mouseY < 84){
		show_command = 3;
		show_Blocks();
		return;
	}
	
	// move 7,87
	if (mouseX > 7 && mouseX < 36 && mouseY > 87 && mouseY < 99){
		show_command = 4;
		show_Blocks();
		return;
	}
	
	// sound 
	if (mouseX > 7 && mouseX < 36 && mouseY > 100 && mouseY < 111){
		// gfx_PrintStringXY("X", 30, 100);
		gfx_PopupMessage("Message: ","Calculator does not support sound.", 0, gfx_orange);
	}
	
	// say 7,114
	if (mouseX > 7 && mouseX < 36 && mouseY > 114 && mouseY < 126){
		show_command = 5;
		show_Blocks();
		return;
	}
	
	// add sprite 
	if (mouseX > newsprt_x && mouseX < newsprt_width + newsprt_x && mouseY > 196 && mouseY < 196 + newsprt_height){
		// gfx_sprites_box();
		if (proj.spriteAmount != 3){
			proj.spriteAmount++;
			
			costumes[proj.spriteAmount - 1].sprite = randInt(1,6);
			Set_Costumes_Data();
			update_sprites_box();
			
			canvas_update();
			for (n = 0; n < proj.spriteAmount; n++){
				sprite_update();
			}
		}
	}
	
	// Costumes #1
	if (mouseX > 185  && mouseX < 218 && mouseY > 186 && mouseY < 232){
		if (mouseY >= 197){
			if (proj.spriteAmount >= 1){
				if (spriteN != 0){
					spriteN = 0;
					update_sprites_box();
					gfx_ClearCodeBox();
					gfx_load_code();
				}
			}
		}else{
			if (proj.spriteAmount > 1){
				costume_Delete(0);
			}
		}	
	}
	
	// Costumes #2
	if (mouseX > 230  && mouseX < 263 && mouseY > 186 && mouseY < 232){
		if (proj.spriteAmount >= 2){
			if (mouseY >= 197){
				if (spriteN != 1){
					spriteN = 1;
					update_sprites_box();
					gfx_ClearCodeBox();
					gfx_load_code();
				}
			}else{
				costume_Delete(1);
			}
		}
	}
	
	// Costumes #3
	if (mouseX > 275  && mouseX < 308 && mouseY > 186 && mouseY < 232){
		if (proj.spriteAmount >= 3){
			if (mouseY >= 197){
				if (spriteN != 2){
					spriteN = 2;
					update_sprites_box();
					gfx_ClearCodeBox();
					gfx_load_code();
				}
			}else{
				costume_Delete(2);
			}
		}
	}
	
	// commands
	// 1
	if (mouseX > 45 && mouseX < 165 && mouseY > 49 && mouseY < 61){
		if (data[spriteN].codeX <= 5){
			switch (show_command){
				case 1:
					data[spriteN].code[data[spriteN].codeX] = 11;
				break;
			
				case 2:
					data[spriteN].code[data[spriteN].codeX] = 21;
				break;
			
				case 3:
					data[spriteN].code[data[spriteN].codeX] = 31;
				break;
				
				case 4:
					data[spriteN].code[data[spriteN].codeX] = 41;
				break;
				
				case 5:
					data[spriteN].code[data[spriteN].codeX] = 51;
				break;
			
				default: 
				break;
			}
		gfx_CodeShow(1);
		data[spriteN].codeX += 1;
		wait(5);
		}
	return;
	}
	
	//2
	if (mouseX > 45 && mouseX < 165 && mouseY > 64 && mouseY < 76){
		if (data[spriteN].codeX <= 5){
			switch (show_command){
				case 1:
					data[spriteN].code[data[spriteN].codeX] = 12;
				break;
			
				case 2:
					data[spriteN].code[data[spriteN].codeX] = 22;
				break;
			
				case 3:
					data[spriteN].code[data[spriteN].codeX] = 32;
				break;
				
				case 4:
					data[spriteN].code[data[spriteN].codeX] = 42;
				break;
				
				case 5:
					data[spriteN].code[data[spriteN].codeX] = 52;
				break;
			
				default: 
				break;
			}
		gfx_CodeShow(2);
		data[spriteN].codeX += 1;
		wait(5);
		}
	
	return;
	}
	
	//3
	if (mouseX > 45 && mouseX < 165 && mouseY > 79 && mouseY < 91){
		if (data[spriteN].codeX <= 5){
			switch (show_command){
				case 1:
					data[spriteN].code[data[spriteN].codeX] = 13;
				break;
			
				case 2:
					data[spriteN].code[data[spriteN].codeX] = 23;
				break;
			
				case 3:
					data[spriteN].code[data[spriteN].codeX] = 33;
				break;
				
				case 4:
					data[spriteN].code[data[spriteN].codeX] = 43;
				break;
				
				case 5:
					data[spriteN].code[data[spriteN].codeX] = 53;
				break;
				
				default: 
				break;
			}
		gfx_CodeShow(3);
		data[spriteN].codeX += 1;
		wait(5);
		}
	return;
	}
	
	// 4
	if (mouseX > 45 && mouseX < 165 && mouseY > 95 && mouseY < 107){
		if (data[spriteN].codeX <= 5){
			switch (show_command){
				case 1:
					data[spriteN].code[data[spriteN].codeX] = 14;
				break;
			
				case 2:
					return;
				break;
			
				case 3:
					data[spriteN].code[data[spriteN].codeX] = 34;
				break;
				
				case 4:
					data[spriteN].code[data[spriteN].codeX] = 44;
				break;
					
				case 5:
					data[spriteN].code[data[spriteN].codeX] = 54;
				break;
					
				default: 
				break;
			}
		gfx_CodeShow(4);
		data[spriteN].codeX += 1;
		wait(5);
		}
	return;
	}

	// 5
	if (mouseX > 45 && mouseX < 165 && mouseY > 110 && mouseY < 122){
		if (data[spriteN].codeX != 6){
			switch (show_command){
				case 1:
					data[spriteN].code[data[spriteN].codeX] = 15;
				break;
			
				case 2:
					return;
				break;
			
				case 3:
					return;
				break;
				
				case 4:
					return;
				break;
				
				case 5:
					data[spriteN].code[data[spriteN].codeX] = 55;
				break;
			
				default: 
				break;
			}
		gfx_CodeShow(5);
		data[spriteN].codeX += 1;
		wait(5);
		}
	return;
	}
	wait(5);
	return;
}

/*
void mouseEnter_load(void){
	// why go the hard way knowing there is a easy way out <_<
	if (mouseX > 80 && mouseX < 241 && mouseY > 70 && mouseY < 171){
		// check if empty space next to tabs was clicked
		if (mouseX > 145 && mouseX < 241 && mouseY > 70 && mouseY < 79){
			Reset_Display_Type();
			return;
		}
		// recent
		if (mouseX > 80 && mouseX < 111 && mouseY > 70 && mouseY < 94){
			load_box_display = 0;
			load_box_display_update();
		}
		// files
		if (mouseX > 114 && mouseX < 144 && mouseY > 70 && mouseY < 79){
			load_box_display = 1;
			load_box_display_update();
		}
		wait(3);
	}else{
		Reset_Display_Type();
		return;
	}
	
}

void mouseEnter_sprites(void){
	if (mouseX > 80 && mouseX < 241 && mouseY > 70 && mouseY < 171){
		// this where detection goes
		wait(5);
	}else{
		Reset_Display_Type();
		wait(5);
		return;
	}
}

void Reset_Display_Type(void){
	gfx_Sprite(Temp_Sprite, 80, 70);
	free(Temp_Sprite);
	Display_Type = 0;
}
*/

int mouse_Hover(void){
	
	// check what is on the screen
	/*if (Display_Type > 0){
		switch (Display_Type){
			case 1:
			//mouseHover_load();
			break;
				
			case 2:
			//mouseHover_sprites();
			break;
		}
		return 0; // fix later	
	}*/
	
	//share
	if (mouseX > 104 && mouseX < 143 && mouseY > 6 && mouseY < 27) return 1;
	
	// load
	if (mouseX > 155 && mouseX < 197 && mouseY > 6 && mouseY < 27) return 1;
	
	// close
	if (mouseX > 296 && mouseX < 316 && mouseY > 7 && mouseY < 27) return 1;
	
	// bg left 179, 40
	if (mouseX > 179 && mouseX < 187 && mouseY > 40 && mouseY < 52) return 1;
	
	// bg right 216, 40
	if (mouseX > 216 && mouseX < 224 && mouseY > 40 && mouseY < 52) return 1;
	
	// add bg 194, 39
	if (mouseX > 194 && mouseX < 209 && mouseY > 39 && mouseY < 52) return 1;
	
	// run 280,39
	if (mouseX > 280 && mouseX < 292 && mouseY > 39 && mouseY < 52) return 1;
	
	// stop 301, 39
	if (mouseX > 301 && mouseX < 314 && mouseY > 39 && mouseY < 52) return 1;
	
	// looks 7,45
	if (mouseX > 7 && mouseX < 36 && mouseY > 45 && mouseY < 57) return 1;
	
	// contr 7,59
	if (mouseX > 7 && mouseX < 36 && mouseY > 59 && mouseY < 71) return 1;
	
	// rotate 7,72
	if (mouseX > 7 && mouseX < 36 && mouseY > 72 && mouseY < 84) return 1;
	
	// move 7,87
	if (mouseX > 7 && mouseX < 36 && mouseY > 87 && mouseY < 99) return 1;
	
	// sound 7, 100
	if (mouseX > 7 && mouseX < 36 && mouseY > 100 && mouseY < 111) return 1;
	
	// say 7,114
	if (mouseX > 7 && mouseX < 36 && mouseY > 114 && mouseY < 126) return 1;
	
	// add sprite btn
	if (mouseX > newsprt_x && mouseX < newsprt_width + newsprt_x && mouseY > 196 && mouseY < 196 + newsprt_height && proj.spriteAmount != 3) return 1;
	
	// Costumes #1
	if (mouseX > 185  && mouseX < 218 && mouseY > 186 && mouseY < 232 && proj.spriteAmount >= 1) return 1;
	
	// Costumes #2
	if (mouseX > 230  && mouseX < 263 && mouseY > 186 && mouseY < 232 && proj.spriteAmount >= 2) return 1; 
	
	// Costumes #3
	if (mouseX > 275  && mouseX < 308 && mouseY > 186 && mouseY < 232 && proj.spriteAmount >= 3) return 1;
	
	// commands
	if (mouseX > 45 && mouseX < 165 && mouseY > 49 && mouseY < 61) return 1;
	
	if (mouseX > 45 && mouseX < 165 && mouseY > 64 && mouseY < 76) return 1;
	
	if (mouseX > 45 && mouseX < 165 && mouseY > 79 && mouseY < 91) return 1;
	
	if (mouseX > 45 && mouseX < 165 && mouseY > 95 && mouseY < 107){
		if (show_command != 2){
			return 1;
		}
	}

	if (mouseX > 45 && mouseX < 165 && mouseY > 110 && mouseY < 122){
		if (show_command == 1 || show_command  == 5){
			return 1;
		}
	}
	
	return 0;
}

// this where mouse hover goes

void show_Blocks(void){
	gfx_SetColor(255);
	gfx_FillRectangle(45, 49, 121, 73);
	gfx_SetTransparentColor(0xF0);
	switch(show_command){
		case 1:
			btns = gfx_MallocSprite(btns_A_width,btns_A_height);
			zx7_Decompress(btns, btns_A_compressed);
			gfx_TransparentSprite(btns, 39, 37);
			free(btns);
		break;
		
		case 2:
			btns = gfx_MallocSprite(btns_B_width, btns_B_height);
			zx7_Decompress(btns, btns_B_compressed);
			gfx_TransparentSprite(btns, 39, 37);
			free(btns);
		break;
		
		case 3:
			btns = gfx_MallocSprite(btns_C_width, btns_C_height);
			zx7_Decompress(btns, btns_C_compressed);
			gfx_TransparentSprite(btns, 39, 37);
			free(btns);
		break;
		
		case 4:
			btns = gfx_MallocSprite(btns_D_width, btns_D_height);
			zx7_Decompress(btns, btns_D_compressed);
			gfx_TransparentSprite(btns, 39, 37);
			free(btns);
		break;
		
		case 5:
			btns = gfx_MallocSprite(btns_F_width, btns_F_height);
			zx7_Decompress(btns, btns_F_compressed);
			gfx_TransparentSprite(btns, 39, 37);
			free(btns);
		break;
	}
	// gfx_Blit(1);	
	return;
}	

void Render_Mouse(void){
	if (!mouse_Hover()){
			cursorA = gfx_MallocSprite(cursorA_width,cursorA_height);
			zx7_Decompress(cursorA, cursorA_compressed);
			gfx_TransparentSprite(cursorA, mouseX, mouseY);
			free(cursorA);
		}else{
			cursorB	= gfx_MallocSprite(cursorB_width,cursorB_height);
			zx7_Decompress(cursorB, cursorB_compressed);
			gfx_TransparentSprite(cursorB, mouseX, mouseY);
			free(cursorB);
	}
	
}

void mouse_keys(void){
	switch (key){
		case kb_Down:
			if (mouseY + mouseSP < LCD_HEIGHT) mouseY += mouseSP;
		break;
	
		case kb_Up:
			if (mouseY - mouseSP > 0) mouseY -= mouseSP;
		break;
			
		case kb_Left:
			if (mouseX - mouseSP > 0) mouseX -= mouseSP;
		break;

		case kb_Right:
			if (mouseX + mouseSP < LCD_WIDTH) mouseX += mouseSP;
		break;
	}
		
	if (kb_IsDown(kb_KeyUp) && kb_IsDown(kb_KeyRight)){
		if (mouseY - mouseSP > 0) mouseY -= mouseSP;
		if (mouseX + mouseSP < LCD_WIDTH) mouseX += mouseSP;
	}
		
	if (kb_IsDown(kb_KeyUp) && kb_IsDown(kb_KeyLeft)){
		if (mouseY - mouseSP > 0) mouseY -= mouseSP;
		if (mouseX - mouseSP > 0) mouseX -= mouseSP;
	}
		
	if (kb_IsDown(kb_KeyDown) && kb_IsDown(kb_KeyRight)){
		if (mouseY + mouseSP < LCD_HEIGHT) mouseY += mouseSP;
		if (mouseX + mouseSP < LCD_WIDTH) mouseX += mouseSP;
	}
		
	if (kb_IsDown(kb_KeyDown) && kb_IsDown(kb_KeyLeft)){
		if (mouseY + mouseSP < LCD_HEIGHT) mouseY += mouseSP;
		if (mouseX - mouseSP > 0) mouseX -= mouseSP;
	}
}

void other_keys(void){
		if (kb_IsDown(kb_KeyAlpha) && kb_IsDown(kb_KeyUp)){
			if (mouseSP != 10) mouseSP += 1;
			gfx_PopupMessage("Message: ","Speed increased. +1 " + mouseSP, 1, gfx_yellow);
		}
		if (kb_IsDown(kb_KeyAlpha) && kb_IsDown(kb_KeyDown)){
			if (mouseSP != 1) mouseSP -= 1;
			gfx_PopupMessage("Message: ","Speed decreased. -1" + mouseSP, 1, gfx_yellow);
		}
		if (kb_Data[6] == kb_Enter || kb_Data[1] == kb_2nd){ // 2nd or Enter
			wait(5); // slows down clicking
			mouse_Enter();
		}
		
		if (kb_Data[6] == kb_Add){
			if (spriteN != proj.spriteAmount - 1){
				delay(5);
				spriteN++;
				update_sprites_box();
				gfx_ClearCodeBox();
				gfx_load_code();
			}
		}		
		
		if (kb_Data[6] == kb_Sub){
			if (spriteN != 0){
				delay(5);
				spriteN--;
				update_sprites_box();
				gfx_ClearCodeBox();
				gfx_load_code();	
			}
		}
		
		// does not run any code below if display is not 0
		// if (Display_Type > 0) return;
		
		// Del
		if (kb_Data[1] == kb_Del){ 
			wait(5); // slows down
			
			if (data[spriteN].code[data[spriteN].codeX] == 0 && data[spriteN].codeX != 0){
				data[spriteN].codeX -= 1;
			}
			
			data[spriteN].code[data[spriteN].codeX] = 0;
			gfx_DeleteCode();
		}
		
		// [mode] = Runcode
		if (kb_Data[1] == kb_Mode){ // mode (runs the user code)
			wait(2);
			runcode();
			return;
		}
		
		return;
}

