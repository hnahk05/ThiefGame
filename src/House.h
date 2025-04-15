#ifndef HOUSE_H
#define HOUSE_H

#include <vector>
#include <SDL.h>

class House {
private:
    SDL_Surface* maskSurface;
    Uint32 getPixel(int x, int y);

public:
    House();
    ~House();

    bool isColliding(int x, int y);
};

#endif
