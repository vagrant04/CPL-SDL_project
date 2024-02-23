//
// Created by 29000 on 2024/1/22.
//
#include "game.h"
#include <hero.h>
#include <math.h>
#include <utils/land.h>
#include <utils/display.h>
#include <utils/input.h>
#include <utils/audio.h>

extern Hero hero;

int back_y = BACK_Y;
int score;
bool have_execute;

void do_game_logic() {
    LOG("Playing")
    if (Mix_PlayingMusic()) Mix_HaltMusic();
    init_background();
    init_hero(); //初始化棋子
    init_land(); //初始化跳板

    Uint32 CD_start, CD_now;
    bool land_flag = false, is_charge = false;
    int force = 0;
    score = 0;
    int Land = rand() % 6;
    
    head = (LanD *) malloc(sizeof (LanD));
    *head = (LanD) {.land = Land, .center_x = DISPLAY_LAND_CENTER_X, .center_y = DISPLAY_LAND_CENTER_Y};//链表初始化
    pre_land = head;
    new_land = head;

    draw_game_background(back_y);//绘制背景
    draw_land(Land, DISPLAY_LAND_CENTER_X, DISPLAY_LAND_CENTER_Y);
    hero_fall(Land); //生成小人

    while (game_state == InGame && !app.keyboard[SDL_SCANCODE_ESCAPE]) {
        do_game_input();
        if (!land_flag) { //未生成新跳板
            creat_land(score); //据分数随机生成跳板
            Land = new_land->land;
            land_fall(Land, new_land->center_x, new_land->center_y);     //新跳板坠落动画  传入中心坐标

            pre_land = head;
            head = new_land;
            head->next = pre_land;

            land_flag = true;
        }
        if (app.keyboard[SDL_SCANCODE_SPACE]) { //蓄力
            if (Mix_PlayingMusic()) Mix_HaltMusic();
            is_charge = true;
            force += 3;
            force = MIN(FORCE_LIMIT, force);
        }

        draw_game_background(back_y);//画跳板
        draw_all_land();
        draw_hero(hero, force);//根据蓄力画棋子
        //draw_force(force);//画蓄力槽  放在hero.c里
        write_score(score);
        present();

        CD_now = SDL_GetTicks(); //特殊块的计时
        if (!have_execute && CD_now - CD_start >= 2000 && !is_charge) {
            if (game_land[pre_land->land].action) game_land[pre_land->land].action();
            have_execute = true;
        }

        if (is_charge && !app.keyboard[SDL_SCANCODE_SPACE]) {
            is_charge = false;
            calculate(force);//计算跳跃距离
            hero_jump();//棋子跳跃动画

            if (in_land(pre_land)) {//仍然在当前跳板
                hero_return_center(0); //拉视角
            } else if (in_land(new_land)) {//在新的跳板
                score_up(1);
                hero_return_center(1);

                pre_land = new_land;
                CD_start = SDL_GetTicks();//计时
                have_execute = false;
                land_flag = false;
            } else { //GameOver
                game_state = Gameover;
            }
            force = 0;
        }
    }

    saveHighScore();//将最高分保存在 “History Hightest Score"里
    quit_background();
    quit_land();
    quit_hero();
}

void init_background() {
    back_y = BACK_Y;
    game_back_surface = IMG_Load("./res/img/background/background_game.jpg");
    game_back_texture = SDL_CreateTextureFromSurface(app.renderer, game_back_surface);
}
void quit_background() {
    SDL_DestroyTexture(game_back_texture);
    SDL_FreeSurface(game_back_surface);
}
void do_game_input() {
    SDL_Event event;
    SDL_PollEvent(&event);
    do_event(event);
}

void draw_game_background(int back_y) {
    SDL_SetRenderDrawColor(app.renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(app.renderer);

    SDL_Rect src_rect = {0, MAX(0, back_y), BACK_W, BACK_H};
    SDL_Rect dst_rect = {0, 0, WIN_W, WIN_H};
    draw_rect(game_back_texture, &src_rect, &dst_rect);
}

void write_score(int score) {
    char buf[16];
    sprintf(buf, "SCORE : %d", score);
    blit_text(buf, 50, 376, 16, color_black, font_widget);
}
void score_up(int num){
    score += num;
}
int getHighScore() {
    int highScore = 0;
    FILE* file = fopen(SCORE_FILE_PATH, "r");
    if (file != NULL) {
        fscanf(file, "%d", &highScore);
        fclose(file);
    }
    return highScore;
}

// 保存最高分数
void saveHighScore() {
    int high_score = getHighScore();
    if (score > high_score) {
        FILE* file = fopen(SCORE_FILE_PATH, "w");
        if (file != NULL) {
            fprintf(file, "%d", score);
            fclose(file);
        }
    }
}

bool in_land(LanD *Land) {
    int hero_button_center_x = hero.next_x + HERO_W / 2;
    int hero_button_center_y = hero.next_y + HERO_H - DISTANCE_FROM_BUTTON_TO_REAL_CENTER;

    int x = abs(hero_button_center_x - Land->center_x);
    int y = abs(hero_button_center_y - Land->center_y);

    if (Land->shape == RECTANGLE) {
        if (x + 2*y <= 2*game_land[Land->land].y) return true; // 矩形判定
    } else {
        if (pow(x, 2)/25.0 + pow(y, 2)/9.0 <= pow(game_land[Land->land].x, 2)/100.0) return true; //圆形判定
    }
    return false;
}