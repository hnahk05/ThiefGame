#include "House.h"

House::House() {
    loadHouse();
}

void House::loadHouse() {
    furniture.push_back({200, 200, 50, 50});
    furniture.push_back({300, 150, 60, 60});
}

bool House::checkCollision(SDL_Rect &rect) {
    for (const auto &obj : furniture) {
        if (SDL_HasIntersection(&rect, &obj)) {
            return true;
        }
    }
    return false;
}

void House::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (const auto &obj : furniture) {
        SDL_RenderFillRect(renderer, &obj);
    }
}
