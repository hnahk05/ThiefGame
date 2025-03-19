#include "DropPoint.h"

DropPoint::DropPoint(int x, int y, int itemID) : targetItemID(itemID) {
    area = {x, y, 30, 30};
}

bool DropPoint::checkDrop(SDL_Rect &thiefPosition, int carriedItem) {
    return (SDL_HasIntersection(&thiefPosition, &area) && carriedItem == targetItemID);
}

void DropPoint::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &area);
}
