#ifndef RUNCODE_H
#define RUNCODE_H

#include <tice.h>
#include <graphx.h>
// functions 
void runcode(void);
 
void code_commands(void);

// void codeDebug(void);
 
void say_commands(void);

void canvas_update(void);

void sprite_update(void);

void load_sprites(int pos);

// external Vars
struct costume_t{
	int active; //bool 
	int x; 
	int y; 
	int s; 
	int r; 
	int vis; //bool	
	int side; //bool
	int compressed; //bool
	int sprite;
	int width;
	int height;
};
extern struct costume_t costumes[3];

extern gfx_sprite_t *costume_SPT;

struct canvas_t{
	int bg;
	int mxbg;
};
extern struct canvas_t stage;

extern int code_running;

extern int n;
#endif
