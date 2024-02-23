//
// Created by 29000 on 2024/1/22.
//

#ifndef AUDIO_H
#define AUDIO_H

#include <common.h>

Mix_Music *music_land;
Mix_Music *menu_bgm;
Mix_Music *kun_music;
Mix_Music *boom_kun_music;

Mix_Chunk *boom_sound;
Mix_Chunk *money_sound;
Mix_Chunk *gameover_sound;
Mix_Chunk *jump_sound;


void play_land_music();

void init_audio();
void quit_audio();

#endif //AUDIO_H
