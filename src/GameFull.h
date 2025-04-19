#ifndef GAME_FULL_H
#define GAME_FULL_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "DropPoint.h"
#include "Thief.h"
#include "Graphics.h"
#include "House.h"

class GameFull {
public:
    GameFull();
    ~GameFull();
    bool init();
    void run();
    void render();
    void update();
    void handleEvents();
    void renderStartScreen();
    bool isPointInRect(int x, int y, const SDL_Rect& rect);

private:
    bool running;
    bool gameStarted;
    int dogAlert;
    SDL_Texture* startScreenTexture;
    SDL_Texture* playButtonTexture;
    SDL_Rect playButtonRect;
    Thief* thief;
    Graphics graphics;
};

#endif // GAME_FULL_H
