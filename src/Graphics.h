#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>

class Graphics {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;


public:
    Graphics();
    ~Graphics();
    bool init();
    void drawNoiseBar(SDL_Renderer* renderer);
    void clear();
    void present();
    SDL_Renderer* getRenderer();
};

extern int noiseLevel;

#endif
