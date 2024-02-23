//
// Created by 29000 on 2024/1/22.
//

#include "utils/input.h"

void do_event(SDL_Event event){
    switch (event.type) {
        case SDL_QUIT:
            do_quit(event.quit);
        break;
        case SDL_KEYDOWN :
            do_keydown(event.key);
        break;
        case SDL_KEYUP :
            do_keyup(event.key);
        break;
        case SDL_MOUSEBUTTONUP:
            do_mousebuttonup(event.button);
        break;
        case SDL_MOUSEBUTTONDOWN:
            do_mousebuttondown(event.button);
        break;
        default:
            break;
    }
}
static void do_quit(SDL_QuitEvent quit) {
    app.keyboard[SDL_SCANCODE_ESCAPE] = true;
}
static void do_keyup(SDL_KeyboardEvent key) {
    app.keyboard[key.keysym.scancode] = false;
}
static void do_keydown(SDL_KeyboardEvent key) {
    app.keyboard[key.keysym.scancode] = true;
}
static void do_mousebuttondown(SDL_MouseButtonEvent button) {
    SDL_GetMouseState(&mouse.x, &mouse.y);
}
static void do_mousebuttonup(SDL_MouseButtonEvent button) {
    mouse.x = -1;
    mouse.y = -1;
}

bool in_rect(int mouse_x, int mouse_y, int rect_x, int rect_y, int rect_w, int rect_h) {
    if (mouse_x - rect_x >= 0 && mouse_x - rect_x <= rect_w && mouse_y - rect_y >= 0 && mouse_y - rect_y <= rect_h) return true;
    return false;
}