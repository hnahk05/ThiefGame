#include "Thief.h"
#include "defs.h"
#include <vector>

extern int noiseLevel;
SDL_Texture* backgroundTexture = nullptr;

Thief::Thief(SDL_Renderer* renderer)
    : renderer(renderer), frameIndex(0), frameDelay(0),
      movingLeft(false), movingRight(false), movingUp(false), movingDown(false),
      facingLeft(false), texture(nullptr), foregroundTexture(nullptr) {

    camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    SDL_Surface* bgSurface = IMG_Load("assets/background.png");
    SDL_Surface* fgSurface = IMG_Load("assets/foreground.png");
    std::string path = "assets/Thief.png";
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
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

bool Thief::checkCollision(const SDL_Rect& a, const Item& item) {
    SDL_Rect b = item.getRect();
    return (a.x < b.x + b.w && a.x + a.w > b.x &&
            a.y < b.y + b.h && a.y + a.h > b.y);
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
        camera.x = std::min(BACKGROUND_WIDTH - SCREEN_WIDTH, camera.x + CAMERA_SPEED);
        nextPos.x = centerX + MOVE_RANGE + camera.x;
    } else if (relativeX < -MOVE_RANGE) {
        camera.x = std::max(0, camera.x - CAMERA_SPEED);
        nextPos.x = centerX - MOVE_RANGE + camera.x;
    }

    if (relativeY > MOVE_RANGE) {
        camera.y = std::min(BACKGROUND_HEIGHT - SCREEN_HEIGHT, camera.y + CAMERA_SPEED);
        nextPos.y = centerY + MOVE_RANGE + camera.y;
    } else if (relativeY < -MOVE_RANGE) {
        camera.y = std::max(0, camera.y - CAMERA_SPEED);
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

    // Chọn các điểm để kiểm tra va chạm, ví dụ 4 góc
    int pointsToCheck[4][2] = {
        { nextCollisionRect.x, nextCollisionRect.y },
        { nextCollisionRect.x + nextCollisionRect.w - 1, nextCollisionRect.y },
        { nextCollisionRect.x, nextCollisionRect.y + nextCollisionRect.h - 1 },
        { nextCollisionRect.x + nextCollisionRect.w - 1, nextCollisionRect.y + nextCollisionRect.h - 1 }
    };

    for (int i = 0; i < 4; ++i) {
        if (house.isColliding(pointsToCheck[i][0], pointsToCheck[i][1])) {
            isColliding = true;
            break;
        }
    }

    if (!isColliding) {
        dstRect = nextPos;
        collisionRect = nextCollisionRect;
    } else {
        noiseLevel += 5;
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

        // ====== DEBUG: Vẽ vùng va chạm ======
    SDL_Rect debugRect = {
        collisionRect.x - camera.x,
        collisionRect.y - camera.y,
        collisionRect.w,
        collisionRect.h
    };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Màu đỏ
    SDL_RenderDrawRect(renderer, &debugRect);

}

SDL_Rect Thief::getRect() const {
    return dstRect;
}
