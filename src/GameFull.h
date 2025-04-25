#ifndef GAMEFULL_H
#define GAMEFULL_H

#include "Graphics.h"
#include "House.h"
#include <SDL_mixer.h>

class Thief;
class Item;

class GameFull {
public:
    GameFull();
    ~GameFull();
    bool init();
    void run();
    void handleEvents(); //xu li thao tac ban phim, chuot
    void update();
    void render();
    static bool checkCollision(SDL_Rect a, SDL_Rect b);
    void resetGame();
    void collectItem(); // Hàm để tăng itemsDelivered

private:
    //thanh phan chinh
    Graphics graphics;
    Thief* thief;
    Item* items;
    House house;
    //trang thai game
    bool running;
    bool gameStarted;
    bool gameEnded;
    int itemsDelivered;
    //do hoa, am thanh
    SDL_Texture* startScreenTexture;
    SDL_Texture* playButtonTexture;
    SDL_Texture* loseScreenTexture;
    SDL_Texture* winScreenTexture;
    SDL_Rect playButtonRect;
    Mix_Music* backgroundMusic;
    Mix_Chunk* memeSound;
    //man hinh bat dau, ket thuc
    void renderStartScreen();
    void renderEndScreen();
    bool isPointInRect(int x, int y, const SDL_Rect& rect);
};

#endif
