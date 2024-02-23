//
// Created by 29000 on 2024/1/22.
//

#ifndef COMMON_H
#define COMMON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define WIN_X 480
#define WIN_Y 120
#define WIN_W 640
#define WIN_H 720
#define FPS 60
#define FRAME_LEN (1000 / FPS)
#define SCORE_FILE_PATH "Historical Highest Score.txt"
#define HANDLE_ERROR(msg) printf(msg ":%s\n", SDL_GetError());\
exit(EXIT_FAILURE);

#define LOG(msg) printf(msg"\n");
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool *keyboard; // calloc vs malloc
} App;
extern App app;
extern SDL_Color color_black;
extern SDL_Color color_white;
typedef enum GameState {
    InMenu,
    InGame,
    Gameover,
    Quit
}GameState;
extern GameState game_state;
typedef struct {
    int x, y;
} Mouse;
extern Mouse mouse;

typedef void (*WidgetAction)();
typedef struct {
    char const* texture;  //文本
    int x, y, w, h;
    WidgetAction action; //操作
} Widget;

#endif //COMMON_H
