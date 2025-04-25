#define SDL_MAIN_HANDLED // Giúp SDL không thay đổi hàm main() thành SDL_main().
#include "SDL.h"
#include "GameFull.h"
#include <iostream>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) { //khoi tao sdl xu li hinh anh va am thanh
        return 1;
    }

    GameFull game;
    if (!game.init()) {
        SDL_Quit(); //khoi tao gamefull that bai thi thoat luon
        return 1;
    }

    game.run(); //chay game

    SDL_Quit(); //thoat game
    return 0;
}
