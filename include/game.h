//
// Created by 29000 on 2024/1/22.
//

#ifndef GAME_H
#define GAME_H

#include <common.h>
#include <utils/land.h>

#define BACK_Y 1216
#define BACK_W 512
#define BACK_H 576

#define FORCE_LIMIT 380

extern SDL_Surface *game_back_surface;
extern SDL_Texture *game_back_texture;

extern TTF_Font *font_widget;

typedef enum {
    RECTANGLE, //矩形
    CIRCLE, //圆
} Shape;
typedef void (*LandAction)();
typedef struct LanD{
    int land;
    int x, y;
    int w, h;
    int side_height;
    int side_y;
    int center_x, center_y;
    LandAction action;
    Shape shape; //矩形 或 圆形
    struct LanD *next;
} LanD;
LanD *pre_land, *new_land;
LanD game_land[LAND_NUM];
LanD *head;

typedef enum {
    LEFT = -1,
    RIGHT = 1,
} Direction;
Direction direction;

void init_background();
void quit_background();
void do_game_input();
void do_game_logic();
void draw_game_background(int back_y);
void write_score(int score);
void score_up(int num);
int getHighScore();
void saveHighScore();

bool in_land(LanD *Land);

#endif //GAME_H
