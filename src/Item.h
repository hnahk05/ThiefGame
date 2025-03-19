#ifndef ITEM_H
#define ITEM_H

#include <SDL.h>

class Item {
private:
    int id;
    SDL_Rect position;
    bool isCarried;

public:
    Item(int id, int x, int y);
    void render(SDL_Renderer *renderer);
    SDL_Rect getPosition();
};

#endif
