#include "Item.h"

Item::Item(int id, int x, int y) : id(id), isCarried(false) {
    position = {x, y, 30, 30};
}

void Item::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &position);
}

SDL_Rect Item::getPosition() {
    return position;
}
