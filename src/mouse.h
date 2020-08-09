// everthing mouse related is in here!!
#ifndef MOUSE_H
#define MOUSE_H

#include <tice.h>
#include <keypadc.h>

// functions
void display_mouse(void);

void mouse_Enter(void);

int mouse_Hover(void);

void show_Blocks(void);

void other_keys(void);

void mouse_keys(void);

void Render_Mouse(void);

// void mouseEnter_load(void);

// void mouseEnter_sprites(void);

// void Reset_Display_Type(void);

// external Vars 
extern kb_key_t key;

extern gfx_sprite_t *behind_sprite;

extern int mouseX;

extern int mouseY;

extern int show_command;

// extern uint8_t Display_Type;

// extern int load_box_display;
#endif