#include "Item.h"

#include <cstdio>

Item::Item(int x, int y, int w, int h) {
    rect = { x, y, w, h };
    texture = nullptr; // Không có ảnh thì để trống
}

Item::Item(SDL_Renderer* renderer, const char* imagePath, int x, int y, int w, int h) {
    // Load ảnh của Item
    SDL_Surface* loadedSurface = IMG_Load(imagePath);
    if (!loadedSurface) {
        printf("Không thể load ảnh %s! SDL_Error: %s\n", imagePath, SDL_GetError());
        texture = nullptr;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    // Đặt vị trí và kích thước
    rect = { x, y, w, h };
}
SDL_Rect rect;

SDL_Rect Item::getRect() const {
    return rect;
}

Item::~Item() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Item::render(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
}
