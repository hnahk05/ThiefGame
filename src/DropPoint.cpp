#include "DropPoint.h"

const char* dropPaths[ITEM_TYPE_COUNT] = {
    "assets/droppoint/alcohol_drop.png",
    "assets/droppoint/clock_drop.png",
    "assets/droppoint/computer_drop.png",
    "assets/droppoint/money_drop.png",
    "assets/droppoint/phone_drop.png",
};

DropPoint::DropPoint(SDL_Renderer* renderer, int x, int y, ItemType expectedType)
    : expectedType(expectedType), satisfied(false) {
    rect = { x, y, 50, 50 };
    SDL_Surface* surface = IMG_Load(dropPaths[expectedType]);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

DropPoint::~DropPoint() {
    SDL_DestroyTexture(texture);
}

void DropPoint::render(SDL_Renderer* renderer, const SDL_Rect& camera) {
    if (!satisfied) {
        SDL_Rect renderRect = {
            rect.x - camera.x,
            rect.y - camera.y,
            rect.w,
            rect.h
        };
        SDL_RenderCopy(renderer, texture, nullptr, &renderRect);
    }
}

SDL_Rect DropPoint::getRect() const { return rect; }

bool DropPoint::isSatisfied() const { return satisfied; }

bool DropPoint::tryDrop(ItemType type) {
    if (type == expectedType && !satisfied) {
        satisfied = true;
        return true;
    }
    return false;
}
