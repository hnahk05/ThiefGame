#define SDL_MAIN_HANDLED // Giúp SDL không thay đổi hàm main() thành SDL_main().
#include "SDL.h"
#include "GameFull.h"
#include <iostream>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        return 1;
    }

    GameFull game;
    if (!game.init()) {
        SDL_Quit();
        return 1;
    }

    game.run();

    SDL_Quit();
    return 0;
}
