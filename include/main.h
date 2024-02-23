//
// Created by 29000 on 2024/1/22.
//

#ifndef MAIN_H
#define MAIN_H

#include <common.h>

SDL_Surface *start_back_surface;
SDL_Surface *start_widget_surface[2];
SDL_Surface *game_back_surface;

SDL_Texture *start_back_texture;
SDL_Texture *start_widget_texture[2];
SDL_Texture *game_back_texture;

TTF_Font *font_widget;
TTF_Font *font_score;

SDL_Color color_black;
SDL_Color color_white;

static void init_app();
static void quit_app();

#endif //MAIN_H
