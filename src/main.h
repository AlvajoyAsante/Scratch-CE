#ifndef MAIN_H
#define MAIN_H

#include <tice.h>
#include <fileioc.h>

// fucntions
// void Debug(void);

void wait(const int amount);

void vars_int(void);

void gfx_PopupMessage(const char *header, const char *message, int type, int color);

void Set_Costumes_Data(void);

// extern vars
extern int i;

extern int temp;

extern uint8_t error; 

extern int spriteN;

extern char *Temp_Char;
// extern sturct 
struct vars_t{
	int spriteAmount;
	char *name;
};
extern struct vars_t proj;
#endif