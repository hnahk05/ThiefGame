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

GameFull::~GameFull() {
    if (thief) {
        delete thief;
        thief = nullptr;
    }
    if (startScreenTexture) {
        SDL_DestroyTexture(startScreenTexture);
        startScreenTexture = nullptr;
    }
    if (playButtonTexture) {
        SDL_DestroyTexture(playButtonTexture);
        playButtonTexture = nullptr;
    }
}

bool GameFull::isPointInRect(int x, int y, const SDL_Rect& rect) {
    return (x >= rect.x && x <= rect.x + rect.w &&
            y >= rect.y && y <= rect.y + rect.h);
}

bool GameFull::init() {
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) return false;

    SDL_Surface* startSurface = IMG_Load("assets/start.jpg");
    if (!startSurface) return false;
    startScreenTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), startSurface);
    SDL_FreeSurface(startSurface);
    if (!startScreenTexture) return false;

    SDL_Surface* playSurface = IMG_Load("assets/play.png");
    if (!playSurface) return false;
    playButtonTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), playSurface);
    SDL_FreeSurface(playSurface);
    if (!playButtonTexture) return false;

    playButtonRect = {
        (SCREEN_WIDTH - buttonWidth) / 2,
        (SCREEN_HEIGHT - buttonHeight) / 2,
        buttonWidth,
        buttonHeight
    };
    return true;
}

void GameFull::renderStartScreen() {
    SDL_RenderClear(graphics.getRenderer());
    SDL_RenderCopy(graphics.getRenderer(), startScreenTexture, NULL, NULL);
    SDL_RenderCopy(graphics.getRenderer(), playButtonTexture, NULL, &playButtonRect);
    SDL_RenderPresent(graphics.getRenderer());
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

    thief->render(graphics.getRenderer());
    graphics.drawNoiseBar(graphics.getRenderer());
    SDL_RenderPresent(graphics.getRenderer());
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

bool checkCollision(SDL_Rect a, SDL_Rect b) {
    if (a.x + a.w <= b.x) return false;
    if (a.x >= b.x + b.w) return false;
    if (a.y + a.h <= b.y) return false;
    if (a.y >= b.y + b.h) return false;
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
