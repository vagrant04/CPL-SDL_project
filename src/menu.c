//
// Created by 29000 on 2024/1/22.
//

#include "menu.h"
#include <utils/display.h>
#include <utils/input.h>
#include <utils/audio.h>
#include <game.h>
#include <main.h>

void do_menu_logic() {
    init_startup();//初始化 画 字 音
    draw_menu();// 显示菜单

    SDL_Event event;
    while (!app.keyboard[SDL_SCANCODE_ESCAPE] && SDL_WaitEvent(&event)) {
        do_event(event);//读取键盘操作 鼠标点击

        bool op = false;
        for (int i = 0; i < WIDGET_NUM; i++) {//   判断选择哪个选项
            op = in_rect(mouse.x, mouse.y, widget_menu[i].x, widget_menu[i].y, widget_menu[i].w, widget_menu[i].h);
            if (op) {
                widget_menu[i].action();
                break;
            }
        }
        if (op) break;
    }
    quit_startup();//结束 画 字 音
}

void init_startup() {
    start_back_surface = IMG_Load("./res/img/background/background_menu.png");
    start_back_texture = SDL_CreateTextureFromSurface(app.renderer, start_back_surface);

    widget_menu = calloc(WIDGET_NUM, sizeof(*widget_menu));
    widget_menu[0] = (Widget){"Start", WIDGET_X, WIDGET_Y_TOP,WIDGET_W, WIDGET_H, start_game};
    widget_menu[1] = (Widget){"Quit", WIDGET_X+40, WIDGET_Y_TOP + WIDGET_GAP,WIDGET_W-80, WIDGET_H, quit_game};

    start_widget_surface[0] = TTF_RenderText_Blended(font_widget, widget_menu[0].texture, color_black);
    start_widget_surface[1] = TTF_RenderText_Blended(font_widget, widget_menu[1].texture, color_black);

    start_widget_texture[0] = SDL_CreateTextureFromSurface(app.renderer, start_widget_surface[0]);
    start_widget_texture[1] = SDL_CreateTextureFromSurface(app.renderer, start_widget_surface[1]);

    Mix_PlayMusic(menu_bgm, -1);//播放音乐
}
void quit_startup() {
    for (int i = 0; i < WIDGET_NUM; i++) {
        SDL_DestroyTexture(start_widget_texture[i]);
        SDL_FreeSurface(start_widget_surface[i]);
    }
    free(widget_menu);
    SDL_DestroyTexture(start_back_texture);
    SDL_FreeSurface(start_back_surface);

    Mix_HaltMusic();//停止音乐
}
void draw_menu() {
    SDL_Rect src_rect_back = {320,0, WIN_W, WIN_H};
    SDL_Rect dst_rect_back = {0, 0, WIN_W, WIN_H};
    draw_rect(start_back_texture, &src_rect_back, &dst_rect_back);

    int hightest_score = getHighScore();
    char buf[30];
    sprintf(buf, "Highest Score : %d", hightest_score);
    blit_text(buf, 24, 340, 26, color_black, font_score);

    for (int i = 0; i < WIDGET_NUM; i++) {
        SDL_Rect dst_rect_widget = {widget_menu[i].x, widget_menu[i].y, widget_menu[i].w, widget_menu[i].h};
        draw_rect(start_widget_texture[i], NULL, &dst_rect_widget);
    }
    present();
}

void start_game() {
    game_state = InGame;
}
void quit_game() {
    game_state = Quit;
}