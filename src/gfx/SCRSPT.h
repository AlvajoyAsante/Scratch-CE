// convpng v7.3
// this file contains all the graphics sources for easy inclusion in a project
#ifndef __SCRSPT__
#define __SCRSPT__
#include <stdint.h>

#include <stdbool.h>

#define SCRSPT_num 35

extern uint8_t *SCRSPT[35];
#define code_box_width 168
#define code_box_height 103
#define code_box_compressed ((gfx_sprite_t*)SCRSPT[0])
#define command_box_width 168
#define command_box_height 98
#define command_box_compressed ((gfx_sprite_t*)SCRSPT[1])
#define sprite_box_width 144
#define sprite_box_height 60
#define sprite_box_compressed ((gfx_sprite_t*)SCRSPT[2])
#define run_box_width 144
#define run_box_height 141
#define run_box_compressed ((gfx_sprite_t*)SCRSPT[3])
#define share_load_width 93
#define share_load_height 23
#define share_load_compressed ((gfx_sprite_t*)SCRSPT[4])
#define small_logo_width 58
#define small_logo_height 22
#define small_logo_compressed ((gfx_sprite_t*)SCRSPT[5])
#define cursorA_width 17
#define cursorA_height 22
#define cursorA_compressed ((gfx_sprite_t*)SCRSPT[6])
#define cursorB_width 17
#define cursorB_height 22
#define cursorB_compressed ((gfx_sprite_t*)SCRSPT[7])
#define btns_A_width 128
#define btns_A_height 96
#define btns_A_compressed ((gfx_sprite_t*)SCRSPT[8])
#define btns_B_width 128
#define btns_B_height 96
#define btns_B_compressed ((gfx_sprite_t*)SCRSPT[9])
#define btns_C_width 128
#define btns_C_height 96
#define btns_C_compressed ((gfx_sprite_t*)SCRSPT[10])
#define btns_D_width 128
#define btns_D_height 96
#define btns_D_compressed ((gfx_sprite_t*)SCRSPT[11])
#define btns_F_width 128
#define btns_F_height 96
#define btns_F_compressed ((gfx_sprite_t*)SCRSPT[12])
#define cat_width 50
#define cat_height 53
#define cat_compressed ((gfx_sprite_t*)SCRSPT[13])
#define dog_width 31
#define dog_height 39
#define dog_compressed ((gfx_sprite_t*)SCRSPT[14])
#define fish_width 50
#define fish_height 55
#define fish_compressed ((gfx_sprite_t*)SCRSPT[15])
#define frog_width 68
#define frog_height 64
#define frog_compressed ((gfx_sprite_t*)SCRSPT[16])
#define clock_width 55
#define clock_height 69
#define clock_compressed ((gfx_sprite_t*)SCRSPT[17])
#define shrek_width 69
#define shrek_height 56
#define shrek_compressed ((gfx_sprite_t*)SCRSPT[18])
#define bg02_width 142
#define bg02_height 120
#define bg02_compressed ((gfx_sprite_t*)SCRSPT[19])
#define bg03_width 142
#define bg03_height 120
#define bg03_compressed ((gfx_sprite_t*)SCRSPT[20])
#define bg04_width 142
#define bg04_height 120
#define bg04_compressed ((gfx_sprite_t*)SCRSPT[21])
#define bg05_width 142
#define bg05_height 120
#define bg05_compressed ((gfx_sprite_t*)SCRSPT[22])
#define bg06_width 142
#define bg06_height 120
#define bg06_compressed ((gfx_sprite_t*)SCRSPT[23])
#define newsprt_width 37
#define newsprt_height 37
#define newsprt_compressed ((gfx_sprite_t*)SCRSPT[24])
#define spriteicon_nul_width 35
#define spriteicon_nul_height 46
#define spriteicon_nul_compressed ((gfx_sprite_t*)SCRSPT[25])
#define spriteicon_sel_width 35
#define spriteicon_sel_height 46
#define spriteicon_sel_compressed ((gfx_sprite_t*)SCRSPT[26])
#define logo_width 148
#define logo_height 45
#define logo_compressed ((gfx_sprite_t*)SCRSPT[27])
#define close_width 20
#define close_height 20
#define close_compressed ((gfx_sprite_t*)SCRSPT[28])
#define arrow_width 12
#define arrow_height 7
#define arrow_compressed ((gfx_sprite_t*)SCRSPT[29])
#define fullscreen_width 14
#define fullscreen_height 14
#define fullscreen_compressed ((gfx_sprite_t*)SCRSPT[30])
#define marker_width 7
#define marker_height 7
#define marker_compressed ((gfx_sprite_t*)SCRSPT[31])
#define sprites_box_width 161
#define sprites_box_height 101
#define sprites_box_compressed ((gfx_sprite_t*)SCRSPT[32])
#define load_box_width 161
#define load_box_height 101
#define load_box_compressed ((gfx_sprite_t*)SCRSPT[33])
#define sizeof_sprites_pal 512
#define sprites_pal ((uint16_t*)SCRSPT[34])
bool SCRSPT_init(void);

#endif
