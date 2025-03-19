#ifndef DROPPOINT_H
#define DROPPOINT_H

#include <SDL.h>

class DropPoint {
private:
    SDL_Rect area;
    int targetItemID;

public:
    DropPoint(int x, int y, int itemID);
    bool checkDrop(SDL_Rect &thiefPosition, int carriedItem);
    void render(SDL_Renderer *renderer);
};

#endif
