//
// Created by 29000 on 2024/1/22.
//

#include "utils/display.h"

#include <main.h>

void init_display() {

    font_score = TTF_OpenFont("./res/font/score_font.ttf", 64);
    font_widget = TTF_OpenFont("./res/font/widget_font_2.otf", 64);

    color_black = (SDL_Color){0x00,0x00,0x00,0xff};
    color_white = (SDL_Color){0xff,0xff,0xff,0xff};
}
void quit_display() {

    TTF_CloseFont(font_widget);
    TTF_CloseFont(font_score);
}
void draw_rect(SDL_Texture *texture, SDL_Rect *src_rect, SDL_Rect *dst_rect) {
    SDL_RenderCopy(app.renderer, texture, src_rect, dst_rect);
}
void blit_text(char *text, int ptsize, int x, int y, SDL_Color color, TTF_Font* font) {
    TTF_SetFontSize(font, ptsize);
    SDL_Surface *surface_text = TTF_RenderText_Blended(font, text, color);
    SDL_Texture *texture_text = SDL_CreateTextureFromSurface(app.renderer, surface_text);

    SDL_Rect rect_text = {.x = x, .y = y};
    SDL_QueryTexture(texture_text, NULL, NULL, &rect_text.w, &rect_text.h);
    SDL_RenderCopy(app.renderer, texture_text, NULL, &rect_text);

    SDL_FreeSurface(surface_text);
    SDL_DestroyTexture(texture_text);
}
void present() {
    Uint32 duration = SDL_GetTicks() - tick;
    tick = SDL_GetTicks();
    Uint32 fps = 1000 / duration;
    char buf[16];
    sprintf(buf, "FPS : %u", fps);
    blit_text(buf, 50, 26, 16, color_black, font_widget);

    Uint32 frame_time = SDL_GetTicks() - frame_start;
    if ((int) (FRAME_LEN - frame_time) > 0) SDL_Delay((int) (FRAME_LEN - frame_time));
    else SDL_Delay(FRAME_LEN);

    frame_start = SDL_GetTicks();
    SDL_RenderPresent(app.renderer);
}