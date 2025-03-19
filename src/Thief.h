#ifndef THIEF_H
#define THIEF_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

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

public:
    Thief(SDL_Renderer* renderer);
    ~Thief();

    void handleInput(const SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);
};

#endif
