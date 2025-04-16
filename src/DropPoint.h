#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Item.h"

class DropPoint {
public:
    DropPoint(SDL_Renderer* renderer, int x, int y, ItemType expectedType);
    ~DropPoint();

    void render(SDL_Renderer* renderer, const SDL_Rect& camera);
    SDL_Rect getRect() const;
    bool isSatisfied() const;
    bool tryDrop(ItemType type);

private:
    SDL_Texture* texture;
    SDL_Rect rect;
    ItemType expectedType;
    bool satisfied;
};
