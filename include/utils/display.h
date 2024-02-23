//
// Created by 29000 on 2024/1/22.
//

#ifndef DISPLAY_H
#define DISPLAY_H

#include <common.h>

Uint32 tick, frame_start;

void init_display();
void quit_display();

void draw_rect(SDL_Texture *texture, SDL_Rect *src_rect, SDL_Rect *dst_rect);
void blit_text(char *text, int ptsize, int x, int y, SDL_Color color, TTF_Font* font);
void present();
#endif //DISPLAY_H
