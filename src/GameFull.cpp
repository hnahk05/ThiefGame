#include "GameFull.h"
#include "Thief.h"
#include "Item.h"
#include <iostream>
#include <SDL_image.h>
#include <defs.h>
using namespace std;

GameFull::GameFull() : graphics(), thief(nullptr), items(nullptr), house(),
                       running(true), gameStarted(false),
                       startScreenTexture(nullptr), playButtonTexture(nullptr) {
    if (graphics.init()) {
        thief = new Thief(graphics.getRenderer());
        items = new Item(graphics.getRenderer(), FIXED_X, FIXED_Y);
        items->spawnItem();
    }
}

GameFull::~GameFull() {
    if (thief) {
        delete thief;
        thief = nullptr;
    }
    if (items) {
        delete items;
        items = nullptr;
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

    SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(graphics.getRenderer());

    thief->render(graphics.getRenderer());
    items->render(graphics.getRenderer(), thief->getCameraX(), thief->getCameraY());
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
            thief->handleInput(event, items);
        }
    }
}

bool GameFull::checkCollision(SDL_Rect a, SDL_Rect b) {
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
}

void GameFull::run() {
    while (running) {
        handleEvents();
        update();
        render();
        SDL_Delay(16);
    }
}
