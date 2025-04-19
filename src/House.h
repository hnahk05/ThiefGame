#ifndef HOUSE_H
#define HOUSE_H

#include <SDL.h>

class House {
private:
    SDL_Surface* maskSurface;
public:
    House();
    ~House();
    Uint32 getPixel(int x, int y);
    bool isColliding(int x, int y);
};

#endif
