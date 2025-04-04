#ifndef THIEF_H
#define THIEF_H

#include <SDL.h>
#include <SDL_image.h>
#include "Item.h"

#include <iostream>
#include <vector>
using namespace std;


class Thief {
private:
    SDL_Texture* texture;
    SDL_Rect srcRect, dstRect;
    SDL_Rect camera;
    SDL_Renderer* renderer;
    int frameIndex;
    int frameDelay;
    bool movingLeft = false;
    bool movingRight = false;
    bool movingUp = false;
    bool movingDown = false;
    bool facingLeft;
    vector<Item> items; // Danh sách vật phẩm

public:
    Thief(SDL_Renderer* renderer);
    ~Thief();
    bool checkCollision(const SDL_Rect&, const Item&);
    void handleInput(const SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);
};

#endif
