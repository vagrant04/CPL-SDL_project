//
// Created by 29000 on 2024/1/22.
//

#ifndef HERO_H
#define HERO_H

#include <common.h>

#define HERO_SCALE_X (20)
#define HERO_SCALE_Y (9)

#define HERO_X ((WIN_W - WIN_W / HERO_SCALE_X) / 2)
#define HERO_Y (((WIN_H - WIN_H / HERO_SCALE_Y) / 2) + 100)
#define HERO_W (WIN_W / HERO_SCALE_X)
#define HERO_H (WIN_H / HERO_SCALE_Y)
#define DISTANCE_FROM_BUTTON_TO_REAL_CENTER 7

#define HERO_JUMP_TIME 1
#define GRAVITY 1
#define SOUND_DIS 10

typedef struct {
    int x, y;
    int vx, vy;
    int next_x, next_y;
} Hero;

SDL_Surface *surface_hero;
SDL_Texture *texture_hero;

void init_hero();
void quit_hero();

void draw_hero(Hero hero, int force);
void draw_force(int force);
void draw_score_up(int scoreup, int x, int y);

void calculate(int force);
void hero_fall(int land);
void hero_jump();
void hero_return_center(int scoreup);

#endif //HERO_H
