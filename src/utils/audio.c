//
// Created by 29000 on 2024/1/22.
//

#include "utils/audio.h"

void play_land_music() {
    Mix_PlayMusic(kun_music, 0);
}

void init_audio() {
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);

    menu_bgm = Mix_LoadMUS("./res/sound/menu_bgm.mp3");
    kun_music = Mix_LoadMUS("./res/sound/kunkun.mp3");
    boom_kun_music = Mix_LoadMUS("./res/sound/boom_kun_sound.mp3");

    boom_sound = Mix_LoadWAV("./res/sound/BOOM_sound.mp3");
    money_sound = Mix_LoadWAV("./res/sound/money_sound.mp3");
    gameover_sound = Mix_LoadWAV("./res/sound/gameover_sound.mp3");
    jump_sound = Mix_LoadWAV("./res/sound/jump_sound.mp3");
}
void quit_audio() {
    Mix_FreeMusic(menu_bgm);
    Mix_FreeMusic(kun_music);
    Mix_FreeMusic(boom_kun_music);

    Mix_FreeChunk(boom_sound);
    Mix_FreeChunk(money_sound);
    Mix_FreeChunk(gameover_sound);
    Mix_FreeChunk(jump_sound);

    Mix_CloseAudio();
}