#include "Thief.h"
#include "defs.h"
#include <vector>
using namespace std;
extern int noiseLevel;
SDL_Texture* backgroundTexture = nullptr;

Thief::Thief(SDL_Renderer* renderer)
    : renderer(renderer), frameIndex(0), frameDelay(0),
      movingLeft(false), movingRight(false), movingUp(false), movingDown(false),
      facingLeft(false), texture(nullptr), foregroundTexture(nullptr) {

    camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    SDL_Surface* bgSurface = IMG_Load("assets/background.png");
    SDL_Surface* fgSurface = IMG_Load("assets/foreground.png");
    SDL_Surface* loadedSurface = IMG_Load("assets/Thief.png");
    if (!loadedSurface || !bgSurface || !fgSurface) {
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    foregroundTexture = SDL_CreateTextureFromSurface(renderer, fgSurface);
    SDL_FreeSurface(loadedSurface);
    SDL_FreeSurface(bgSurface);
    SDL_FreeSurface(fgSurface);

    if (!texture || !backgroundTexture || !foregroundTexture) {
        return;
    }

    srcRect = {0, 0, FRAME_WIDTH, FRAME_HEIGHT};

    // Initialize character position
    dstRect = {startX, startY, FRAME_WIDTH, FRAME_HEIGHT};

    // Initialize collision rectangle
    collisionRect = {
        dstRect.x + COLLISION_OFFSET_X,
        dstRect.y + COLLISION_OFFSET_Y,
        dstRect.w - (2 * COLLISION_OFFSET_X),
        dstRect.h - (2 * COLLISION_OFFSET_Y)
    };

    // Initialize camera position
    camera.x = startX - (SCREEN_WIDTH / 2 - FRAME_WIDTH / 2);
    camera.y = startY - (SCREEN_HEIGHT / 2 - FRAME_HEIGHT / 2);
}

Thief::~Thief() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    if (foregroundTexture) {
        SDL_DestroyTexture(foregroundTexture);
    }
}

void Thief::handleInput(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                movingLeft = true;
                facingLeft = true;
                break;
            case SDLK_RIGHT:
                movingRight = true;
                facingLeft = false;
                break;
            case SDLK_UP:
                movingUp = true;
                break;
            case SDLK_DOWN:
                movingDown = true;
                break;
        }
    }
    else if (event.type == SDL_KEYUP) {
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

void Thief::update(House& house) {
    SDL_Rect nextPos = dstRect;
    frameDelay++;
    if (frameDelay >= 10) {
        frameIndex = (frameIndex + 1) % FRAME_COUNT;
        frameDelay = 0;
    }
    srcRect.x = frameIndex * FRAME_WIDTH;
    if (srcRect.x >= 384) srcRect.x = 0;

    const int centerX = SCREEN_WIDTH / 2 - FRAME_WIDTH / 2;
    const int centerY = SCREEN_HEIGHT / 2 - FRAME_HEIGHT / 2;

    if (movingLeft) nextPos.x -= MOVE_SPEED;
    if (movingRight) nextPos.x += MOVE_SPEED;
    if (movingUp) nextPos.y -= MOVE_SPEED;
    if (movingDown) nextPos.y += MOVE_SPEED;

    int relativeX = nextPos.x - (centerX + camera.x);
    int relativeY = nextPos.y - (centerY + camera.y);

    if (relativeX > MOVE_RANGE) {
        camera.x = min(BACKGROUND_WIDTH - SCREEN_WIDTH, camera.x + CAMERA_SPEED);
        nextPos.x = centerX + MOVE_RANGE + camera.x;
    } else if (relativeX < -MOVE_RANGE) {
        camera.x = max(0, camera.x - CAMERA_SPEED);
        nextPos.x = centerX - MOVE_RANGE + camera.x;
    }

    if (relativeY > MOVE_RANGE) {
        camera.y = min(BACKGROUND_HEIGHT - SCREEN_HEIGHT, camera.y + CAMERA_SPEED);
        nextPos.y = centerY + MOVE_RANGE + camera.y;
    } else if (relativeY < -MOVE_RANGE) {
        camera.y = max(0, camera.y - CAMERA_SPEED);
        nextPos.y = centerY - MOVE_RANGE + camera.y;
    }

    SDL_Rect nextCollisionRect = {
        nextPos.x + COLLISION_OFFSET_X,
        nextPos.y + COLLISION_OFFSET_Y,
        nextPos.w - (2 * COLLISION_OFFSET_X),
        nextPos.h - (2 * COLLISION_OFFSET_Y)
    };

    // === Kiểm tra va chạm bằng mask ===
    bool isColliding = false;

    // Kiểm tra va chạm theo viền khung chữ nhật
    for (int x = nextCollisionRect.x; x < nextCollisionRect.x + nextCollisionRect.w; ++x) {
        if (house.isColliding(x, nextCollisionRect.y) ||  // cạnh trên
            house.isColliding(x, nextCollisionRect.y + nextCollisionRect.h - 1)) {  // cạnh dưới
            isColliding = true;
            break;
        }
    }

    if (!isColliding) {
        for (int y = nextCollisionRect.y; y < nextCollisionRect.y + nextCollisionRect.h; ++y) {
            if (house.isColliding(nextCollisionRect.x, y) ||  // cạnh trái
                house.isColliding(nextCollisionRect.x + nextCollisionRect.w - 1, y)) {  // cạnh phải
                isColliding = true;
                break;
            }
        }
    }

    if (!isColliding) {
        dstRect = nextPos;
        collisionRect = nextCollisionRect;
    } else {
        noiseLevel += 1;
        if (noiseLevel > 100) noiseLevel = 100;
    }
}

void Thief::render(SDL_Renderer* renderer) {
    if (!texture || !backgroundTexture || !foregroundTexture) {
        return;
    }

    // Draw background
    SDL_Rect bgRect = { camera.x, camera.y, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, backgroundTexture, &bgRect, NULL);

    // Draw character
    SDL_Rect renderRect = {
        dstRect.x - camera.x,
        dstRect.y - camera.y,
        dstRect.w,
        dstRect.h
    };

    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, texture, &srcRect, &renderRect, 0, NULL, flip);

    // Draw foreground
    SDL_Rect fgRect = { camera.x, camera.y, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, foregroundTexture, &fgRect, NULL);

}

SDL_Rect Thief::getRect() const {
    return dstRect;
}
