cmake_minimum_required(VERSION 3.27)
project(SDL_Project C)

set(CMAKE_C_STANDARD 17)

add_compile_options(-fcommon)

include_directories(include)
include_directories("D:/programming/SDL2/mingw(CLion+VSC)/SDL2-2.26.0-allinone/x86_64-w64-mingw32/include")
link_directories("D:/programming/SDL2/mingw(CLion+VSC)/SDL2-2.26.0-allinone/x86_64-w64-mingw32/lib")

add_executable(SDL_Project src/main.c
        src/game.c
        src/menu.c
        src/hero.c
        src/utils/display.c
        src/utils/input.c
        src/utils/audio.c
        src/utils/land.c
        src/gameover.c)

target_link_libraries(SDL_Project PRIVATE
        mingw32
        SDL2main
        SDL2
        SDL2_image
        SDL2_mixer
        SDL2_ttf
)