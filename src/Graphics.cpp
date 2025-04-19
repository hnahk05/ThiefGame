#include "Graphics.h"
#include "defs.h"
#include <iostream>

Graphics::Graphics() : window(nullptr), renderer(nullptr) {}

Graphics::~Graphics() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Graphics::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) return false;
    window = SDL_CreateWindow("Thief Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) return false;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) return false;
    return true;
}

void Graphics::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

int noiseLevel = 0;
//vẽ thanh tiếng ồn
void Graphics::drawNoiseBar(SDL_Renderer* renderer) {
    // Vẽ viền đen
    SDL_Rect borderRect = { 48, 18, 204, 24 }; // Lớn hơn thanh tiếng ồn 2px mỗi bên
    SDL_SetRenderDrawColor(renderer, 3, 8, 13, 255);
    SDL_RenderFillRect(renderer, &borderRect);

    // Vẽ thanh nền
    SDL_Rect barBackground = { 50, 20, 200, 20 };
    SDL_SetRenderDrawColor(renderer, 75, 173, 218, 255);
    SDL_RenderFillRect(renderer, &barBackground);

    // Vẽ viền đen của thanh tiếng ồn
    SDL_Rect noiseBorder = { 50, 20, 2 * noiseLevel, 20 };
    SDL_SetRenderDrawColor(renderer, 10, 11, 15, 255);
    SDL_RenderFillRect(renderer, &noiseBorder);

    // Vẽ phần nhỏ hơn bên trong để tạo viền đen xung quanh
    SDL_Rect noiseBar = { 51, 21, 2 * noiseLevel - 2, 18 };
    if (noiseBar.w > 0) { // Tránh vẽ khi width < 0
        SDL_SetRenderDrawColor(renderer, 252, 252, 252, 255);
        SDL_RenderFillRect(renderer, &noiseBar);
    }
}

void Graphics::present() {
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Graphics::getRenderer() {
    return renderer;
}
