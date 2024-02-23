//
// Created by 29000 on 2024/1/25.

#ifndef LAND_H
#define LAND_H

#include <common.h>
#include <hero.h>

#define LAND_NUM 11
#define LAND_X 200
#define LAND_Y 350
#define LAND_W 500
#define LAND_HIGHT 60
#define TAN_LAN (0.5)

#define DISPLAY_LAND_CENTER_X (HERO_X + HERO_W / 2) //初始中心点
#define DISPLAY_LAND_CENTER_Y (HERO_Y + HERO_H - DISTANCE_FROM_BUTTON_TO_REAL_CENTER)

SDL_Surface *surface_land[LAND_NUM];
SDL_Surface *surface_boom;

SDL_Texture *texture_land[LAND_NUM];
SDL_Texture *texture_boom;

void init_land();
void quit_land();

void creat_land(int score);
void draw_all_land();
void land_fall(int land, int dst_x, int dst_y);
void draw_land(int land, int center_x, int center_y);

void play_music();
void add_score();
void boom();

#endif //LAND_H
