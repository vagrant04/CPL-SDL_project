//
// Created by 29000 on 2024/1/28.
//

#include "../include/gameover.h"

#include <utils/audio.h>
#include <utils/display.h>
#include <utils/input.h>

void do_gameover_logic() {
    LOG("You Die!")
    init_gameover();//初始化 画 字 音
    draw_gameover();

    SDL_Event event;
    while (!app.keyboard[SDL_SCANCODE_ESCAPE] && SDL_WaitEvent(&event)) {
        do_event(event);

        bool op = false;
        for (int i = 0; i < GAMEOVER_WIDGET_NUM; i++) {//   判断选择哪个选项
            op = in_rect(mouse.x, mouse.y, widget_gameover[i].x, widget_gameover[i].y, widget_gameover[i].w, widget_gameover[i].h);
            if (op) {
                widget_gameover[i].action();
                break;
            }
        }
        if (op) break;
    }
    quit_gameover();
}

void init_gameover() {
    gameover_back_surface = IMG_Load("./res/img/background/background_gameover.jpg");
    gameover_back_texture = SDL_CreateTextureFromSurface(app.renderer, gameover_back_surface);

    widget_gameover = calloc(GAMEOVER_WIDGET_NUM, sizeof(*widget_gameover));
    widget_gameover[0] = (Widget){"Home Page", GAMEOVER_WIDGET_X-20, GAMEOVER_WIDGET_Y_TOP,GAMEOVER_WIDGET_W+40, GAMEOVER_WIDGET_H, gameover_return_menu};
    widget_gameover[1] = (Widget){"Restart", GAMEOVER_WIDGET_X, GAMEOVER_WIDGET_Y_TOP + GAMEOVER_WIDGET_GAP,GAMEOVER_WIDGET_W, GAMEOVER_WIDGET_H, gameover_restart_game};
    widget_gameover[2] = (Widget){"Quit", GAMEOVER_WIDGET_X+50, GAMEOVER_WIDGET_Y_TOP + 2*GAMEOVER_WIDGET_GAP,GAMEOVER_WIDGET_W-100, GAMEOVER_WIDGET_H, gameover_quit_game};

    for (int i = 0; i < GAMEOVER_WIDGET_NUM; i++) {
        gameover_widget_surface[i] = TTF_RenderText_Blended(font_widget, widget_gameover[i].texture, color_white);
        gameover_widget_texture[i] = SDL_CreateTextureFromSurface(app.renderer, gameover_widget_surface[i]);
    }

    Mix_PlayChannel(-1, gameover_sound, 0);//死亡音效
}
void quit_gameover() {
    for (int i = 0; i < GAMEOVER_WIDGET_NUM; i++) {
        SDL_DestroyTexture(gameover_widget_texture[i]);
        SDL_FreeSurface(gameover_widget_surface[i]);
    }
    free(widget_gameover);
    SDL_DestroyTexture(gameover_back_texture);
    SDL_FreeSurface(gameover_back_surface);
}
void draw_gameover() {
    SDL_Rect src_rect_back = {640,160, 2 * WIN_W, 2 * WIN_H};
    SDL_Rect dst_rect_back = {0, 0, WIN_W, WIN_H};
    draw_rect(gameover_back_texture, &src_rect_back, &dst_rect_back);

    for (int i = 0; i < GAMEOVER_WIDGET_NUM; i++) {
        SDL_Rect dst_rect_widget = {widget_gameover[i].x, widget_gameover[i].y, widget_gameover[i].w, widget_gameover[i].h};
        draw_rect(gameover_widget_texture[i], NULL, &dst_rect_widget);
    }
    present();
}

void gameover_return_menu() {
    game_state = InMenu;
}
void gameover_restart_game() {
    game_state = InGame;
}
void gameover_quit_game() {
    game_state = Quit;
}