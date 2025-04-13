#include "House.h"
#include "defs.h"

House::House() {
    loadHouse();
}

void House::loadHouse() {
    // Add all wall coordinates
    furniture.push_back({452, 367, 32, 243});
    furniture.push_back({452, 367, 437, 130});
    furniture.push_back({856, 467, 100, 142});
    furniture.push_back({918, 254, 695, 149});
    furniture.push_back({1582, 254, 32, 704});
    furniture.push_back({1349, 958, 264, 241});
    furniture.push_back({1618, 1011, 95, 219});
    furniture.push_back({1680, 1009, 538, 105});
    furniture.push_back({2187, 1008, 28, 560});
    furniture.push_back({905, 1028, 31, 635});
    furniture.push_back({908, 960, 280, 169});
    furniture.push_back({451, 935, 36, 190});
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
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); // Gray color for walls
    for (const auto &obj : furniture) {
        SDL_RenderFillRect(renderer, &obj);
    }
}


SDL_Rect House::getRect() const {
    return SDL_Rect{ x, y, width, height };
}
