#include "GameFull.h"
#include <iostream>
#include <SDL_image.h>

GameFull::GameFull() : running(true), dogAlert(0) {
    if (graphics.init()) {
        thief = new Thief(graphics.getRenderer());
    }
}

bool GameFull::init() {
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        return false;
    }

    // Khởi tạo các vật phẩm với vị trí và kích thước
    items.emplace_back(400, 300, 50, 50);

    // Khởi tạo các điểm thả vật phẩm
    dropPoints.emplace_back(500, 300, 1);

    return true;
}

void GameFull::render() {
    SDL_SetRenderDrawColor(graphics.getRenderer(), 192, 192, 192, 255);
    SDL_RenderClear(graphics.getRenderer());
    thief->render(graphics.getRenderer());
    graphics.drawNoiseBar(graphics.getRenderer());
    graphics.present();
}

void GameFull::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        thief->handleInput(event);
    }
}

void GameFull::update() {
    thief->update();
}

void GameFull::run() {
    while (running) {
        handleEvents();
        update();
        render();
        SDL_Delay(16);
    }
}
