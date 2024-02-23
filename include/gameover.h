//
// Created by 29000 on 2024/1/28.
//

#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <common.h>

#define GAMEOVER_WIDGET_NUM 3
#define GAMEOVER_WIDGET_W 240
#define GAMEOVER_WIDGET_H 60
#define GAMEOVER_WIDGET_X 200
#define GAMEOVER_WIDGET_Y_TOP 450
#define GAMEOVER_WIDGET_GAP 80

SDL_Surface *gameover_back_surface;
SDL_Surface *gameover_widget_surface[GAMEOVER_WIDGET_NUM];

SDL_Texture *gameover_back_texture;
SDL_Texture *gameover_widget_texture[GAMEOVER_WIDGET_NUM];

extern TTF_Font *font_widget;

Widget *widget_gameover;

void do_gameover_logic();

void init_gameover();
void draw_gameover();
void quit_gameover();

void gameover_return_menu();
void gameover_restart_game();
void gameover_quit_game();

#endif //GAMEOVER_H
