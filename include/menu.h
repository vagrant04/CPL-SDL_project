//
// Created by 29000 on 2024/1/22.
//

#ifndef MENU_H
#define MENU_H

#include <common.h>

#define WIDGET_NUM 2
#define WIDGET_W 320
#define WIDGET_H 90
#define WIDGET_X 160
#define WIDGET_Y_TOP 170
#define WIDGET_GAP 120

extern SDL_Surface *start_back_surface;
extern SDL_Surface *start_widget_surface[2];

extern SDL_Texture *start_back_texture;
extern SDL_Texture *start_widget_texture[2];

extern TTF_Font *font_widget;

Widget *widget_menu;

void do_menu_logic();

void init_startup();
void draw_menu();
void quit_startup();

void start_game();
void quit_game();

#endif //MENU_H
