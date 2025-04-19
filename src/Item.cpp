#include "Item.h"
#include <iostream>
using namespace std;
#include <defs.h>

Item::Item(SDL_Renderer* renderer, int fixedX, int fixedY)
    : renderer(renderer), Item1Texture(nullptr), Item2Texture(nullptr),
      Item3Texture(nullptr), Item4Texture(nullptr), Item5Texture(nullptr),
      currentItemIndex(-1), pickedUp(false) {

    srand(time(0));

    SDL_Surface* surface1 = IMG_Load("assets/alcohol.png");
    if (!surface1) return;
    SDL_Surface* surface2 = IMG_Load("assets/clock.png");
    if (!surface2) return;
    SDL_Surface* surface3 = IMG_Load("assets/computer.png");
    if (!surface3) return;
    SDL_Surface* surface4 = IMG_Load("assets/money.png");
    if (!surface4) return;
    SDL_Surface* surface5 = IMG_Load("assets/phone.png");
    if (!surface5) return;

    Item1Texture = SDL_CreateTextureFromSurface(renderer, surface1);
    Item2Texture = SDL_CreateTextureFromSurface(renderer, surface2);
    Item3Texture = SDL_CreateTextureFromSurface(renderer, surface3);
    Item4Texture = SDL_CreateTextureFromSurface(renderer, surface4);
    Item5Texture = SDL_CreateTextureFromSurface(renderer, surface5);

    if (!Item1Texture || !Item2Texture || !Item3Texture || !Item4Texture || !Item5Texture) return;

    SDL_FreeSurface(surface1);
    SDL_FreeSurface(surface2);
    SDL_FreeSurface(surface3);
    SDL_FreeSurface(surface4);
    SDL_FreeSurface(surface5);

    itemSpawned = vector<bool>(5, false);
    dropPointPlaced = vector<bool>(5, false);
    fixedPosition = {fixedX, fixedY, ITEM_SIZE, ITEM_SIZE};
    position = fixedPosition;
}

Item::~Item() {
    if (Item1Texture) SDL_DestroyTexture(Item1Texture);
    if (Item2Texture) SDL_DestroyTexture(Item2Texture);
    if (Item3Texture) SDL_DestroyTexture(Item3Texture);
    if (Item4Texture) SDL_DestroyTexture(Item4Texture);
    if (Item5Texture) SDL_DestroyTexture(Item5Texture);
}

void Item::spawnItem() {
    bool allSpawned = true;
    for (bool spawned : itemSpawned) {
        if (!spawned) {
            allSpawned = false;
            break;
        }
    }
    if (allSpawned) {
        currentItemIndex = -1;
        printf("Tất cả item đã xuất hiện!\n");
        return;
    }

    int itemIndex;
    do {
        itemIndex = rand() % 5;
    } while (itemSpawned[itemIndex]);

    currentItemIndex = itemIndex;
    itemSpawned[itemIndex] = true;
    position = fixedPosition;
    pickedUp = false;
}

void Item::pickUp() {
    pickedUp = true;
}

void Item::drop(int x, int y) {
    pickedUp = false;
    position.x = x;
    position.y = y;
    if (currentItemIndex >= 0) {
        dropPointPlaced[currentItemIndex] = true;
    }
    spawnItem();
}

void Item::updatePosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void Item::render(SDL_Renderer* renderer, int cameraX, int cameraY) {
    if (currentItemIndex == -1) return;

    SDL_Rect renderRect = {
        position.x - cameraX,
        position.y - cameraY,
        ITEM_SIZE,
        ITEM_SIZE
    };

    switch (currentItemIndex) {
        case 0:
            SDL_RenderCopy(renderer, Item1Texture, NULL, &renderRect);
            break;
        case 1:
            SDL_RenderCopy(renderer, Item2Texture, NULL, &renderRect);
            break;
        case 2:
            SDL_RenderCopy(renderer, Item3Texture, NULL, &renderRect);
            break;
        case 3:
            SDL_RenderCopy(renderer, Item4Texture, NULL, &renderRect);
            break;
        case 4:
            SDL_RenderCopy(renderer, Item5Texture, NULL, &renderRect);
            break;
    }
}
