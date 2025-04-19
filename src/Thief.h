#ifndef THIEF_H
#define THIEF_H

#include <SDL.h>
#include <SDL_image.h>
#include "Item.h"
#include "House.h" //kiểm tra va chạm với tường và đồ trong nhà

#include <iostream>
#include <vector>
using namespace std;


class Thief {
private:
    SDL_Texture* texture;
    SDL_Texture* foregroundTexture;
    SDL_Texture* ATexture; SDL_Texture* BTexture; SDL_Texture* CTexture; SDL_Texture* DTexture; SDL_Texture* ETexture;
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
    SDL_Rect collisionRect;  // Rectangle for collision detection

public:
    Thief(SDL_Renderer* renderer);
    ~Thief();
    int getCameraX() const { return camera.x; }
    int getCameraY() const { return camera.y; }
    void handleInput(const SDL_Event& event);
    void update(House& House);
    void render(SDL_Renderer* renderer);
    SDL_Rect getRect() const;
};

#endif
