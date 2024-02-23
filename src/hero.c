//
// Created by 29000 on 2024/1/22.
//

#include "hero.h"

#include <game.h>
#include <main.h>
#include <utils/display.h>
#include <utils/input.h>
#include <utils/land.h>
#include "utils/land.h"
#include "utils/audio.h"

Hero hero;
extern int back_y;
extern int score;
extern LanD *head;

void init_hero() {
    hero.x = HERO_X;
    hero.y = HERO_Y;
    hero.vx = 4;
    hero.vy = 20;

    surface_hero = IMG_Load("./res/img/hero/hero.png");
    texture_hero = SDL_CreateTextureFromSurface(app.renderer, surface_hero);
}
void quit_hero() {
    SDL_DestroyTexture(texture_hero);
    SDL_FreeSurface(surface_hero);
}

void draw_hero(Hero hero, int force) {
    SDL_Rect dst_rect = {hero.x - force / 26, hero.y + force / 5, HERO_W + force / 26 * 2 ,HERO_H - force / 5};
    draw_rect(texture_hero, NULL, &dst_rect);
}
void draw_force(int force) {
    SDL_SetRenderDrawColor(app.renderer, 0xff, 0x00, 0x00, 0xff);
    SDL_Rect force_rect = {80, 80, force, 50};
    SDL_RenderFillRect(app.renderer, &force_rect);
}

void hero_fall(int land) {
    for (int y = -HERO_Y, dy = 4; y <= HERO_Y; y += dy, dy += 1) {
        draw_game_background(back_y);
        draw_land(land, DISPLAY_LAND_CENTER_X, DISPLAY_LAND_CENTER_Y);
        SDL_Rect dst_rect = {HERO_X, y, HERO_W, HERO_H};
        draw_rect(texture_hero, NULL, &dst_rect);
        present();
    }
}
void calculate(int force) {
    hero.next_x = hero.x + direction * force;
    hero.next_y = hero.y - force * TAN_LAN;
}
void hero_jump() {
    bool flag_sound = false;
    int x = hero.x;
    int y = hero.y;
    hero.vy = abs(hero.next_x - hero.x) / hero.vx / 2.0 * GRAVITY;

    while (direction * x < direction * hero.next_x && (hero.vy > 0 || y < hero.next_y)) {
        x += direction * hero.vx;
        y -= hero.vy + hero.vx * TAN_LAN * 1.0;
        hero.vy -= GRAVITY;

        if (!flag_sound && abs(hero.next_x - x) >= SOUND_DIS && abs(hero.next_x - x) <= SOUND_DIS + 4) {
            flag_sound = true;
            Mix_PlayChannel(-1, jump_sound, 0);
        } // 播放声音

        SDL_Rect rect = {x,y,HERO_W, HERO_H};
        draw_game_background(back_y);
        draw_all_land();
        draw_rect(texture_hero, NULL, &rect);
        write_score(score);
        present();
    }
}
void hero_return_center(int scoreup) {
    int x = hero.next_x;
    int y = hero.next_y;
    double vy = hero.vx * TAN_LAN;
    int scoreup_h = 80;

    while (direction * x > direction * hero.x) {
        x -= direction * hero.vx;
        y += vy;

        SDL_Rect rect = {x,y,HERO_W, HERO_H};
        draw_game_background(back_y);
        back_y--;

        LanD *ptr = head;
        while (ptr) {
            ptr->center_x -= direction * hero.vx;
            ptr->center_y += vy;
            ptr = ptr->next;
        }

        int scoreup_x = head->center_x;//加分特效
        int scoreup_y = head->center_y - scoreup_h;
        scoreup_h++;
        if (scoreup > 0) draw_score_up(scoreup, scoreup_x, scoreup_y);

        draw_all_land();
        draw_rect(texture_hero, NULL, &rect);
        write_score(score);
        present();
    }

    hero.x = x;
    hero.y = y;//??????
}
void draw_score_up(int scoreup, int x, int y) {
    char buf[16];
    sprintf(buf, "+%d", scoreup);
    blit_text(buf, 36, x, y, color_white, font_score);
}