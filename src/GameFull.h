#ifndef GAMEFULL_H
#define GAMEFULL_H

#include <SDL.h>
#include "Graphics.h"
#include "Thief.h"
#include "House.h"
#include "Item.h"
#include "DropPoint.h"

class GameFull {
private:
    bool running;
    bool gameStarted;
    Graphics graphics;
    Thief* thief;
    House house;
    int dogAlert;
    SDL_Texture* startScreenTexture;
    SDL_Texture* playButtonTexture;
    SDL_Rect playButtonRect;

public:
    GameFull();
    ~GameFull() {
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
    bool init();
    void run();
    void handleEvents();
    void update();
    void render();
    void clean();
    void renderStartScreen();
    bool isPointInRect(int x, int y, const SDL_Rect& rect);
};

#endif
