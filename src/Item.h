#pragma once
#include <SDL.h>
#include <SDL_image.h>

enum ItemType {
    ITEM_ALCOHOL,
    ITEM_CLOCK,
    ITEM_COMPUTER,
    ITEM_MONEY,
    ITEM_PHONE,
    ITEM_TYPE_COUNT
};

class Item {
public:
    Item(SDL_Renderer* renderer, int x, int y, ItemType type);
    ~Item();

    void render(SDL_Renderer* renderer, const SDL_Rect& camera);
    SDL_Rect getRect() const;
    ItemType getType() const;
    bool isCollected() const;
    void collect();

private:
    SDL_Texture* texture;
    SDL_Rect rect;
    ItemType type;
    bool collected;
};
