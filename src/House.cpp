#include "House.h"
#include "defs.h"
#include <SDL_image.h>

House::House() {
    maskSurface = IMG_Load("assets/maskground.png");
    if (!maskSurface) {
        SDL_Log("Failed to load collision mask: %s", IMG_GetError());
    }

}

House::~House() {
    SDL_FreeSurface(maskSurface);
}

Uint32 House::getPixel(int x, int y) {
    int bpp = maskSurface->format->BytesPerPixel;
    Uint8* p = (Uint8*)maskSurface->pixels + y * maskSurface->pitch + x * bpp;

    switch (bpp) {
        case 1: return *p;
        case 2: return *(Uint16*)p;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        case 4: return *(Uint32*)p;
        default: return 0;
    }
}

bool House::isColliding(int x, int y) {
    if (!maskSurface || x < 0 || y < 0 || x >= maskSurface->w || y >= maskSurface->h) return true;

    Uint32 pixel = getPixel(x, y);
    Uint8 r, g, b;
    SDL_GetRGB(pixel, maskSurface->format, &r, &g, &b);

    return (r == 0 && g == 0 && b == 0);  // màu đen là va chạm
}
