#include <main.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <common.h>
#include <game.h>
#include <gameover.h>
#include <menu.h>
#include <utils/audio.h>
#include <utils/display.h>
#undef main

App app;
GameState game_state;
Mouse mouse;

int main(){
    init_app();
    init_display();
    init_audio();

    game_state = InMenu;
    while (!app.keyboard[SDL_SCANCODE_ESCAPE]) {
        if (game_state == InMenu) {//当前在菜单
            do_menu_logic();
        }
        else if (game_state == InGame) {//当前在游戏
            do_game_logic();
        }
        else if (game_state == Gameover) {//
            do_gameover_logic();
        }
        else if (game_state == Quit) {
            return 0;
        }
    }


    atexit(&quit_app);
    atexit(&quit_display);
    atexit(&quit_audio);
    return 0;
}
static void init_app() {
    LOG("Initializing")
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        HANDLE_ERROR("Init SDL")
    }
    if (!IMG_Init(IMG_INIT_JPG)) {
        HANDLE_ERROR("Init Image")

    }
    if (!Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID | MIX_INIT_OPUS )) {
        HANDLE_ERROR("Init Mixer")
    }
    if (TTF_Init() == -1) {
        HANDLE_ERROR("Init TTF")
    }
    app.window = SDL_CreateWindow("Jump One Jump!", WIN_X, WIN_Y, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
    app.keyboard = calloc(SDL_NUM_SCANCODES, sizeof(bool));
}
static void quit_app() {
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    free(app.keyboard);
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
}