#ifndef GUI_H
#define GUI_H

#include <tice.h>
#include <fontlibc.h>
#include <fileioc.h>
#include <string.h>

// function
void gfx_BatteryStatus(void);

void gfx_GetTime(void);

void gfx_GetDate(void);

void splash_screen(void);

void show_ver(void);

void UI_setup(void);

void gfx_load_code(void);

// void gfx_load_box(void);

void update_sprites_box(void);

// void gfx_costumes_box(void);

// void load_box_display_update(void);

void load_sprites(int pos);

void get_Icon(int pos);

// extern vars
extern int8_t ver_type;
extern int8_t ver_maj;
extern int8_t ver_min;

extern fontlib_font_pack_t *my_font_pack;
extern fontlib_font_t *my_font;

extern ti_var_t file;

extern uint8_t error;

extern int newsprt_x;

#endif
