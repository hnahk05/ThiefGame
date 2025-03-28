#include "Thief.h"
#include "defs.h"
#include <vector>

const int FRAME_WIDTH = 192;
const int FRAME_HEIGHT = 192;
const int FRAME_COUNT = 2;

extern int noiseLevel; //Lưu tiếng ồn
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

    camera.x = startX - (SCREEN_WIDTH / 2 - FRAME_WIDTH / 2);
    camera.y = startY - (SCREEN_HEIGHT / 2 - FRAME_HEIGHT / 2);


    dstRect = {startX, startY, FRAME_WIDTH, FRAME_HEIGHT};

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
                if (!movingRight && !movingUp && !movingDown && !movingLeft) {
                    movingLeft = true;
                    movingRight = movingUp = movingDown = false;
                    facingLeft = true;
                }
                break;
            case SDLK_RIGHT:
                if (!movingLeft && !movingUp && !movingDown && !movingRight) {
                    movingRight = true;
                    movingLeft = movingUp = movingDown = false;
                    facingLeft = false;
                }
                break;
            case SDLK_UP:
                if (!movingLeft && !movingRight && !movingDown && !movingUp) {
                    movingUp = true;
                    movingLeft = movingRight = movingDown = false;
                }
                break;
            case SDLK_DOWN:
                if (!movingLeft && !movingRight && !movingUp && !movingDown) {
                    movingDown = true;
                    movingLeft = movingRight = movingUp = false;
                }
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

bool Thief::checkCollision(const SDL_Rect& a, const Item& item) {
    SDL_Rect b = item.getRect();
    b.x -= camera.x;
    b.y -= camera.y;
    return (a.x < b.x + b.w && a.x + a.w > b.x &&
            a.y < b.y + b.h && a.y + a.h > b.y);
}

void Thief::update() {
    SDL_Rect nextPos = dstRect;
    frameDelay++;
    if (frameDelay >= 10) {
        frameIndex = (frameIndex + 1) % FRAME_COUNT;
        frameDelay = 0;
    }
    srcRect.x = frameIndex * FRAME_WIDTH;
    if (srcRect.x >= 384) srcRect.x = 0;

    // Xác định vùng trung tâm nhỏ để nhân vật có thể di chuyển
    const int centerX = SCREEN_WIDTH / 2 - FRAME_WIDTH / 2;
    const int centerY = SCREEN_HEIGHT / 2 - FRAME_HEIGHT / 2;
    const int moveRange = 100;  // Tăng phạm vi di chuyển lên 100px
    const int moveSpeed = 4;

    // Di chuyển nhân vật trong vùng nhỏ - chỉ cho phép một hướng di chuyển tại một thời điểm
    if (movingLeft) {
        nextPos.x -= moveSpeed;
        nextPos.y = dstRect.y; // Giữ nguyên vị trí y
    }
    else if (movingRight) {
        nextPos.x += moveSpeed;
        nextPos.y = dstRect.y; // Giữ nguyên vị trí y
    }
    else if (movingUp) {
        nextPos.y -= moveSpeed;
        nextPos.x = dstRect.x; // Giữ nguyên vị trí x
    }
    else if (movingDown) {
        nextPos.y += moveSpeed;
        nextPos.x = dstRect.x; // Giữ nguyên vị trí x
    }

    // Tính toán vị trí tương đối của nhân vật so với tâm màn hình
    int relativeX = nextPos.x - (centerX + camera.x);
    int relativeY = nextPos.y - (centerY + camera.y);

    // Di chuyển camera khi nhân vật vượt quá vùng cho phép
    if (relativeX > moveRange) {
        camera.x = std::min(BACKGROUND_WIDTH - SCREEN_WIDTH, camera.x + moveSpeed);
        nextPos.x = centerX + moveRange + camera.x;
    }
    else if (relativeX < -moveRange) {
        camera.x = std::max(0, camera.x - moveSpeed);
        nextPos.x = centerX - moveRange + camera.x;
    }

    if (relativeY > moveRange) {
        camera.y = std::min(BACKGROUND_HEIGHT - SCREEN_HEIGHT, camera.y + moveSpeed);
        nextPos.y = centerY + moveRange + camera.y;
    }
    else if (relativeY < -moveRange) {
        camera.y = std::max(0, camera.y - moveSpeed);
        nextPos.y = centerY - moveRange + camera.y;
    }

    // Kiểm tra va chạm với các vật phẩm
    bool isColliding = false;
    for (auto& item : items) {
        if (checkCollision(nextPos, item)) {
            isColliding = true;
            break;
        }
    }

    // Nếu không có va chạm, cập nhật vị trí
    if (!isColliding) {
        dstRect = nextPos;
    } else {
        noiseLevel += 5; // Va chạm thì tăng tiếng ồn
        if (noiseLevel > 100) noiseLevel = 100;
    }
}

void Thief::render(SDL_Renderer* renderer) {
    if (!texture || !backgroundTexture) {
        return;
    }

    // Vẽ background với camera offset
    SDL_Rect bgRect = { camera.x, camera.y, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, backgroundTexture, &bgRect, NULL);

    // Vẽ nhân vật với vị trí tương đối so với camera
    SDL_Rect renderRect = {
        dstRect.x - camera.x,
        dstRect.y - camera.y,
        dstRect.w,
        dstRect.h
    };

    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, texture, &srcRect, &renderRect, 0, NULL, flip);
}


