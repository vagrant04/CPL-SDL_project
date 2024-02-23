//
// Created by 29000 on 2024/1/25.
//

#include "utils/land.h"
#include <game.h>
#include <hero.h>
#include <math.h>
#include <utils/display.h>
#include <utils/audio.h>

extern int back_y;
extern LanD *head;

extern Hero hero;
extern int score;

void creat_land(int score) { //据分数随机生成跳板 //记得用score
    int rdm_direction = rand() % 2;
    if (rdm_direction == 0) direction = LEFT;
    else direction = RIGHT;
    int rdm1 = rand() % 6 + score / 8;
    rdm1 = MIN(LAND_NUM - 1, rdm1);
    int rdm2 = (game_land[pre_land->land].w + game_land[rdm1].w + MAX(0, direction * (pre_land->center_x - DISPLAY_LAND_CENTER_X))) / 4 + 40 + rand() % 100;

    int x = hero.x + HERO_W / 2;
    int y = hero.y + HERO_H - DISTANCE_FROM_BUTTON_TO_REAL_CENTER;
    new_land = malloc(sizeof(LanD));
    new_land->land = rdm1;
    new_land->center_x = x + direction * rdm2;
    new_land->center_y = y - rdm2 * TAN_LAN;
    new_land->shape = game_land[rdm1].shape;
}
void land_fall(int land, int dst_x, int dst_y) { //新跳板坠落动画
    int land_y = game_land[land] . h;
    for (int y = -land_y, dy = 4; y <= dst_y; y += dy, dy += 1) {
        draw_game_background(back_y);
        draw_all_land();

        draw_hero(hero, 0);
        SDL_Rect dst_rect = {dst_x - game_land[land].w / 2, y - game_land[land].y, game_land[land].w,  game_land[land].h};
        draw_rect(texture_land[land], NULL, &dst_rect);
        write_score(score);
        present();
    }
}

void draw_land(int land, int center_x, int center_y) {//画跳板
    int dst_x = center_x - game_land[land].w / 2;
    int dst_y = center_y - game_land[land].y;

    SDL_Rect dst_rect = {dst_x, dst_y, game_land[land].w,  game_land[land].h};
    draw_rect(texture_land[land], NULL, &dst_rect);

    // SDL_SetRenderDrawColor(app.renderer, 0xff, 0, 0, 255);  // 设置颜色为红色
    // for (int xx = 0; xx <= WIN_W; xx++) {
    //     for (int yy = 200; yy <= 600; yy++) {
    //         LanD *Land = head;
    //         while (Land != pre_land->next) {
    //             int x = abs(xx - Land->center_x);
    //             int y = abs(yy - Land->center_y);
    //
    //             if (Land->shape == RECTANGLE) {
    //                 if (x + 2*y <= 2*game_land[Land->land].y) {SDL_RenderDrawPoint(app.renderer, xx, yy);} // 矩形判定
    //             } else {
    //                 if (pow(x, 2)/25.0 + pow(y, 2)/9.0 <= pow(game_land[Land->land].x, 2)/100.0) {SDL_RenderDrawPoint(app.renderer, xx, yy);} //圆形判定
    //             }
    //             Land = Land -> next;
    //         }
    //     }
    // }
}
void draw_all_land() {
    LanD *ptr = head;
    while (ptr) {
        draw_land(ptr -> land, ptr->center_x, ptr->center_y);
        ptr = ptr -> next;
    }
}
void init_land() {
    surface_boom = IMG_Load("./res/img/land/BOOM.png");//初始化爆炸图
    texture_boom = SDL_CreateTextureFromSurface(app.renderer, surface_boom);

    char file_name[30];
    for (int i = 0; i < LAND_NUM; i++) {
        sprintf(file_name, "./res/img/land/land%d.png", i + 1);
        surface_land[i] = IMG_Load(file_name);
        texture_land[i] = SDL_CreateTextureFromSurface(app.renderer, surface_land[i]);
    }

    game_land[0].side_height = 60;
    game_land[1].side_height = 126;
    game_land[2].side_height = 56;
    game_land[3].side_height = 75;
    game_land[4].side_height = 137;
    game_land[5].side_height = 78;
    game_land[6].side_height = 215;
    game_land[7].side_height = 150;
    game_land[8].side_height = 259;
    game_land[9].side_height = 403;
    game_land[10].side_height = 166;
    for (int i = 0; i < LAND_NUM; i++) {
        game_land[i].side_y = (surface_land[i]->h - game_land[i].side_height) / 2 * 1.0;
        game_land[i].w = LAND_HIGHT * surface_land[i]->w / game_land[i].side_height * 1.0;

        game_land[i].x = game_land[i].w;

        game_land[i].y = LAND_HIGHT * game_land[i].side_y / game_land[i].side_height * 1.0;
        game_land[i].h = LAND_HIGHT * surface_land[i]->h / game_land[i].side_height * 1.0;
        game_land[i].shape = RECTANGLE;
    }

    game_land[1].action = play_music;//初始化 特殊跳板
    game_land[3].action = add_score;
    game_land[8].action = boom;

    game_land[5].shape = CIRCLE;//初始化 圆形跳台
    game_land[7].shape = CIRCLE;
    game_land[9].shape = CIRCLE;
    game_land[9].x = 393 * game_land[9].h / surface_land[9]->h;
    game_land[10].shape = CIRCLE;
    game_land[10].x = 103 * game_land[10].h / surface_land[10]->h;
}
void quit_land() {
    SDL_DestroyTexture(texture_boom);
    SDL_FreeSurface(surface_boom);

    for (int i = 0; i < LAND_NUM; i++) {
        SDL_DestroyTexture(texture_land[i]);
        SDL_FreeSurface(surface_land[i]);
    }

    LanD *ptr = head;
    while (ptr) {
        free(ptr);
        ptr = ptr->next;
    }
}

void play_music() {
    play_land_music();
}
void add_score() {
    Mix_PlayChannel(-1, money_sound, 0);
    score_up(5);

    int scoreup_h = 100;
    while (scoreup_h <= 130) {
        int scoreup_x = pre_land->center_x;
        int scoreup_y = pre_land->center_y - scoreup_h;
        scoreup_h++;

        SDL_Rect rect = {hero.x,hero.y,HERO_W, HERO_H};
        draw_game_background(back_y);
        draw_score_up(5, scoreup_x, scoreup_y);
        draw_all_land();
        draw_rect(texture_hero, NULL, &rect);
        write_score(score);
        present();
    }
}
void boom() {
    calculate(500);
    int scale = 2;
    int x = hero.x;
    int y = hero.y;
    hero.vy = abs(hero.next_x - hero.x) / hero.vx / 2.0 * GRAVITY;

    Mix_PlayChannel(-1, boom_sound, 0);
    Mix_PlayMusic(boom_kun_music, 0);
    while (direction * x < direction * hero.next_x && (hero.vy > 0 || y < hero.next_y)) {
        x += direction * hero.vx;
        y -= hero.vy + hero.vx * TAN_LAN * 1.0;
        hero.vy -= GRAVITY;

        int dst_boom_x = pre_land->center_x - (scale - 1) * surface_boom->w * 1.0 / scale / 2.0;
        int dst_boom_y = pre_land->center_y - (scale - 1) * surface_boom->h * 1.0 / scale / 2.0;
        SDL_Rect boom_rect = {dst_boom_x,dst_boom_y,surface_boom->w*1.0*(scale-1)/scale, surface_boom->h*1.0*(scale-1)/scale};
        SDL_Rect rect = {x,y,HERO_W, HERO_H};
        scale++;

        draw_game_background(back_y);
        draw_all_land();
        draw_rect(texture_hero, NULL, &rect);
        write_score(score);
        draw_rect(texture_boom, NULL, &boom_rect);
        present();
    }

    game_state = Gameover;
}