#ifndef GAMEFULL_H
#define GAMEFULL_H

#include "Graphics.h"
#include "House.h"

// Forward declaration cho class Thief và Item
class Thief;
class Item;

class GameFull {
public:
    GameFull();
    ~GameFull();
    bool init();
    void run();
    void handleEvents();
    void update();
    void render();
    static bool checkCollision(SDL_Rect a, SDL_Rect b);
    void resetGame();
    void collectItem(); // Hàm để tăng itemsDelivered

private:
    Graphics graphics;
    Thief* thief;
    Item* items;
    House house;
    bool running;
    bool gameStarted;
    bool gameEnded;
    int itemsDelivered;
    SDL_Texture* startScreenTexture;
    SDL_Texture* playButtonTexture;
    SDL_Texture* loseScreenTexture;
    SDL_Texture* winScreenTexture;
    SDL_Rect playButtonRect;

    void renderStartScreen();
    void renderEndScreen();
    bool isPointInRect(int x, int y, const SDL_Rect& rect);
};

#endif
