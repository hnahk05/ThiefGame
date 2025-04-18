#include "GameFull.h"
#include <iostream>
#include <SDL_image.h>
#include <defs.h>
using namespace std;

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
        cerr << "Failed to load start screen image: " << IMG_GetError() << endl;
        return false;
    }
    startScreenTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), startSurface);
    SDL_FreeSurface(startSurface);
    if (!startScreenTexture) {
        cerr << "Failed to create start screen texture: " << SDL_GetError() << endl;
        return false;
    }

    // Load play button image
    SDL_Surface* playSurface = IMG_Load("assets/play.png");
    if (!playSurface) {
        cerr << "Failed to load play button image: " << IMG_GetError() << endl;
        return false;
    }
    playButtonTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), playSurface);
    SDL_FreeSurface(playSurface);
    if (!playButtonTexture) {
        cerr << "Failed to create play button texture: " << SDL_GetError() << endl;
        return false;
    }

    // Set play button position in the middle of the screen
    playButtonRect = {
        (SCREEN_WIDTH - buttonWidth) / 2,
        (SCREEN_HEIGHT - buttonHeight) / 2,
        buttonWidth,
        buttonHeight
    };

    // Initialize droppoints at specific coordinates
    /*dropPoints.emplace_back(graphics.getRenderer(), 1000, 1300, ITEM_MONEY);
    dropPoints.emplace_back(graphics.getRenderer(), 1460, 430, ITEM_ALCOHOL);
    dropPoints.emplace_back(graphics.getRenderer(), 1740, 1150, ITEM_CLOCK);
    dropPoints.emplace_back(graphics.getRenderer(), 1383, 1166, ITEM_COMPUTER);
    dropPoints.emplace_back(graphics.getRenderer(), 564, 468, ITEM_PHONE);

    // Initialize items at the same positions
    items.emplace_back(graphics.getRenderer(), 1000, 1300, ITEM_MONEY);
    items.emplace_back(graphics.getRenderer(), 1460, 430, ITEM_ALCOHOL);
    items.emplace_back(graphics.getRenderer(), 1740, 1150, ITEM_CLOCK);
    items.emplace_back(graphics.getRenderer(), 1383, 1166, ITEM_COMPUTER);
    items.emplace_back(graphics.getRenderer(), 564, 468, ITEM_PHONE);*/

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

    SDL_Rect camera = {
        thief->getRect().x + thief->getRect().w / 2 - SCREEN_WIDTH / 2,
        thief->getRect().y + thief->getRect().h / 2 - SCREEN_HEIGHT / 2,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    };

    // Vẽ tên trộm
    thief->render(graphics.getRenderer());

    // Vẽ thanh tiếng ồn
    graphics.drawNoiseBar(graphics.getRenderer());

    // Hiển thị ra màn hình
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

House House;
void GameFull::update() {
    if (gameStarted) {
        thief->update(House);
    }
    SDL_Rect thiefRect = thief->getRect();

}

void GameFull::run() {
    while (running) {
        handleEvents();
        update();
        render();
        SDL_Delay(16);
    }
}
