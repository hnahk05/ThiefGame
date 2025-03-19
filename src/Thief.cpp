#include "Thief.h"
#include "defs.h"

const int FRAME_WIDTH = 160;
const int FRAME_HEIGHT = 160;
const int FRAME_COUNT = 2;

Thief::Thief(SDL_Renderer* renderer)
    : renderer(renderer), frameIndex(0), frameDelay(0),
      movingLeft(false), movingRight(false), movingUp(false), movingDown(false),
      facingLeft(false), texture(nullptr) {
    std::string path = "assets/Thief.png";
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (!texture) {
        return;
    }

    srcRect = {0, 0, FRAME_WIDTH, FRAME_HEIGHT};
    dstRect = {200, 300, FRAME_WIDTH, FRAME_HEIGHT};

    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0, NULL, flip);
}

Thief::~Thief() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Thief::handleInput(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                movingLeft = true;
                movingRight = movingUp = movingDown = false;
                facingLeft = true;
                break;
            case SDLK_RIGHT:
                movingRight = true;
                movingLeft = movingUp = movingDown = false;
                facingLeft = false;
                break;
            case SDLK_UP:
                movingUp = true;
                movingLeft = movingRight = movingDown = false;
                break;
            case SDLK_DOWN:
                movingDown = true;
                movingLeft = movingRight = movingUp = false;
                break;
        }
    }
    if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                movingLeft = false;
                break;
            case SDLK_RIGHT:
                movingRight = false;
                break;
            case SDLK_UP:
                movingUp = false;
                break;
            case SDLK_DOWN:
                movingDown = false;
                break;
        }
    }
}


void Thief::update() {
    frameDelay++;
    if (frameDelay >= 10) {
        frameIndex = (frameIndex + 1) % FRAME_COUNT;
        frameDelay = 0;
    }
    srcRect.x = frameIndex * FRAME_WIDTH;
    if (srcRect.x >= 320) srcRect.x = 0;

    if (movingLeft && dstRect.x > 0) dstRect.x -= 5;
    if (movingRight && dstRect.x + FRAME_WIDTH < SCREEN_WIDTH) dstRect.x += 5;
    if (movingUp && dstRect.y > 0) dstRect.y -= 5;
    if (movingDown && dstRect.y + FRAME_HEIGHT < SCREEN_HEIGHT) dstRect.y += 5;
}

void Thief::render(SDL_Renderer* renderer) {
    if (!texture) {
        return;
    }

    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0, NULL, flip);
}
