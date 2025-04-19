#ifndef GAMEFULL_H
#define GAMEFULL_H

#include "Graphics.h"
#include "Thief.h"
#include "House.h"
#include "Item.h" // Thêm include cho Item

class GameFull {
public:
    GameFull();
    ~GameFull();
    bool init();
    void run();
    void handleEvents();
    void update();
    void render();

private:
    Graphics graphics;
    Thief* thief;
    Item* items; // Thêm đối tượng Item
    House house;
    bool running;
    bool gameStarted;
    SDL_Texture* startScreenTexture;
    SDL_Texture* playButtonTexture;
    SDL_Rect playButtonRect;

    void renderStartScreen();
    bool isPointInRect(int x, int y, const SDL_Rect& rect);
};

#endif
