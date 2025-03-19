#include "Thief.h"
#include "defs.h"

const int FRAME_WIDTH = 160;
const int FRAME_HEIGHT = 160;
const int FRAME_COUNT = 2;

SDL_Texture* backgroundTexture = nullptr;

Thief::Thief(SDL_Renderer* renderer)
    : renderer(renderer), frameIndex(0), frameDelay(0),
      movingLeft(false), movingRight(false), movingUp(false), movingDown(false),
      facingLeft(false), texture(nullptr) {

    camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    SDL_Surface* bgSurface = IMG_Load("assets/background.png");
    std::string path = "assets/Thief.png";
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface||!bgSurface) {
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(loadedSurface);
    SDL_FreeSurface(bgSurface);

    if (!texture||!bgSurface) {
        return;
    }

    srcRect = {0, 0, FRAME_WIDTH, FRAME_HEIGHT};
    dstRect = {200, 300, FRAME_WIDTH, FRAME_HEIGHT}; // chỗ nhân vật xuất hiện

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

    // Xác định vùng trung tâm nhỏ để nhân vật có thể di chuyển
    const int centerX = SCREEN_WIDTH / 2 - FRAME_WIDTH / 2;
    const int centerY = SCREEN_HEIGHT / 2 - FRAME_HEIGHT / 2;
    const int moveRange = 50;  // Nhân vật chỉ di chuyển tối đa 50px trong vùng này

    // Di chuyển nhân vật trong vùng nhỏ
    if (movingLeft && dstRect.x > centerX - moveRange) dstRect.x -= 5;
    if (movingRight && dstRect.x < centerX + moveRange) dstRect.x += 5;
    if (movingUp && dstRect.y > centerY - moveRange) dstRect.y -= 5;
    if (movingDown && dstRect.y < centerY + moveRange) dstRect.y += 5;

    // Nếu nhân vật chạm vùng giới hạn, di chuyển camera thay vì nhân vật
    if (movingLeft && dstRect.x <= centerX - moveRange) camera.x = std::max(0, camera.x - 5);
    if (movingRight && dstRect.x >= centerX + moveRange) camera.x = std::min(BACKGROUND_WIDTH - SCREEN_WIDTH, camera.x + 5);
    if (movingUp && dstRect.y <= centerY - moveRange) camera.y = std::max(0, camera.y - 5);
    if (movingDown && dstRect.y >= centerY + moveRange) camera.y = std::min(BACKGROUND_HEIGHT - SCREEN_HEIGHT, camera.y + 5);
}

void Thief::render(SDL_Renderer* renderer) {
    if (!texture||!backgroundTexture) {
        return;
    }
    SDL_Rect bgRect = { camera.x, camera.y, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, backgroundTexture, &bgRect, NULL);

    SDL_Rect renderRect = {
        dstRect.x - camera.x,
        dstRect.y - camera.y,
        dstRect.w,
        dstRect.h
    };

    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0, NULL, flip);
}
