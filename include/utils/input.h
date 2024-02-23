//
// Created by 29000 on 2024/1/22.
//

#ifndef INPUT_H
#define INPUT_H

#include <common.h>

extern App app;

void do_event(SDL_Event event);
static void do_keyup(SDL_KeyboardEvent key);
static void do_keydown(SDL_KeyboardEvent key);
static void do_quit(SDL_QuitEvent quit);
static void do_mousebuttondown(SDL_MouseButtonEvent button);
static void do_mousebuttonup(SDL_MouseButtonEvent button);

bool in_rect(int mouse_x, int mouse_y, int rect_x, int rect_y, int rect_w, int rect_h);

#endif //INPUT_H
