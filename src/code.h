#ifndef CODE_H
#define CODE_H

// #include "defines.h"
#include <tice.h>
#include <graphx.h>
#include <math.h>

// function
void code_show(void);

void gfx_CodeShow(int selected);

void gfx_DeleteCode(void);

void gfx_ClearCodeBox(void);

void costume_Delete(int pos);

void Delete_AllCode(int pos);
// var
struct code_t{
	int code[7];
	int codeX;	
};
extern struct code_t data[3];

extern int codeBY;

extern gfx_sprite_t *command_behind;

#endif