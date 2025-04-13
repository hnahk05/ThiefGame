#include "GameFull.h"
#include <iostream>
#include <SDL_image.h>
#include <defs.h>

GameFull::GameFull() : running(true), gameStarted(false), dogAlert(0),
                      startScreenTexture(nullptr), playButtonTexture(nullptr) {
    if (graphics.init()) {
        thief = new Thief(graphics.getRenderer());
    }
}

bool GameFull::isPointInRect(int x, int y, const SDL_Rect& rect) {
    return (x >= rect.x && x <= rect.x + rect.w &&
            y >= rect.y && y <= rect.y + rect.h);
}

bool GameFull::init() {
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        return false;
    }

    // Load start screen image
    SDL_Surface* startSurface = IMG_Load("assets/start.jpg");
    if (!startSurface) {
        std::cerr << "Failed to load start screen image: " << IMG_GetError() << std::endl;
        return false;
    }
    startScreenTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), startSurface);
    SDL_FreeSurface(startSurface);
    if (!startScreenTexture) {
        std::cerr << "Failed to create start screen texture: " << SDL_GetError() << std::endl;
        return false;
    }

    // Load play button image
    SDL_Surface* playSurface = IMG_Load("assets/play.png");
    if (!playSurface) {
        std::cerr << "Failed to load play button image: " << IMG_GetError() << std::endl;
        return false;
    }
    playButtonTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), playSurface);
    SDL_FreeSurface(playSurface);
    if (!playButtonTexture) {
        std::cerr << "Failed to create play button texture: " << SDL_GetError() << std::endl;
        return false;
    }

    // Set play button position in the middle of the screen
    playButtonRect = {
        (SCREEN_WIDTH - buttonWidth) / 2,
        (SCREEN_HEIGHT - buttonHeight) / 2,
        buttonWidth,
        buttonHeight
    };

    /* Khởi tạo các bức tường
(452, 367, 32, 243);
(452, 367, 437, 130);
(856, 467, 100, 142);
(918, 254, 695, 149);
(1582, 254, 32, 704);
(1349, 958, 264, 241);
(1618, 1011, 95, 219);
(1680, 1009, 538, 105);
(2187, 1008, 28, 560);
(905, 1028, 31, 635);
(908, 960, 280, 169);
(451, 935, 36, 190);*/

    // Khởi tạo các vật phẩm với vị trí và kích thước
    items.emplace_back(400, 300, 50, 50);

    // Khởi tạo các điểm thả vật phẩm
    dropPoints.emplace_back(500, 300, 1);

    return true;
}

void GameFull::renderStartScreen() {
    SDL_RenderClear(graphics.getRenderer());
    SDL_RenderCopy(graphics.getRenderer(), startScreenTexture, NULL, NULL);
    SDL_RenderCopy(graphics.getRenderer(), playButtonTexture, NULL, &playButtonRect);
    graphics.present();
}

void GameFull::render() {
    if (!gameStarted) {
        renderStartScreen();
        return;
    }

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
        if (!gameStarted) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (isPointInRect(mouseX, mouseY, playButtonRect)) {
                    gameStarted = true;
                }
            }
        } else {
            thief->handleInput(event);
        }
    }
}
//xử lí va chạm
bool checkCollision(SDL_Rect a, SDL_Rect b) {
    // Nếu một hình nằm hoàn toàn bên trái của hình kia
    if (a.x + a.w <= b.x) return false;
    if (a.x >= b.x + b.w) return false;

    // Nếu một hình nằm hoàn toàn bên trên của hình kia
    if (a.y + a.h <= b.y) return false;
    if (a.y >= b.y + b.h) return false;

    // Các trường hợp còn lại là có va chạm
    return true;
}


void GameFull::update() {
    if (gameStarted) {
        thief->update();
    }
    SDL_Rect thiefRect = thief->getRect();

    for (auto& item : items) {
        SDL_Rect itemRect = item.getRect();
        if (checkCollision(thiefRect, itemRect)) {
            std::cout << "Thief chạm item!" << std::endl;
        }
    }

}

void GameFull::run() {
    while (running) {
        handleEvents();
        update();
        render();
        SDL_Delay(16);
    }
}
