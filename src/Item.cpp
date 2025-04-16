#include "Item.h"
using namespace std;

const char* itemPaths[ITEM_TYPE_COUNT] = {
    "assets/item/alcohol.png",
    "assets/item/clock.png",
    "assets/item/computer.png",
    "assets/item/money.png",
    "assets/item/phone.png"
};

Item::Item(SDL_Renderer* renderer, int x, int y, ItemType type)
    : type(type), collected(false) {
    rect = { x, y, 50, 50 };
    SDL_Surface* surface = IMG_Load(itemPaths[type]);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Item::~Item() {
    SDL_DestroyTexture(texture);
}

void Item::render(SDL_Renderer* renderer, const SDL_Rect& camera) {
    if (!collected) {
        SDL_Rect renderRect = {
            rect.x - camera.x,
            rect.y - camera.y,
            rect.w,
            rect.h
        };
        SDL_RenderCopy(renderer, texture, nullptr, &renderRect);
    }
}

SDL_Rect Item::getRect() const { return rect; }
ItemType Item::getType() const { return type; }
bool Item::isCollected() const { return collected; }
void Item::collect() { collected = true; }
