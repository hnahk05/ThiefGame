#ifndef ITEM_H
#define ITEM_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <cstdlib>
#include <ctime>

class Item {
public:
    Item(SDL_Renderer* renderer, int fixedX, int fixedY);
    ~Item();
    void spawnItem();
    void render(SDL_Renderer* renderer, int cameraX, int cameraY);
    void pickUp();
    void drop(int x, int y);
    void updatePosition(int x, int y);
    bool isPickedUp() const { return pickedUp; }
    int getCurrentItemIndex() const { return currentItemIndex; }
    bool isDropPointActive(int index) const { return !dropPointPlaced[index]; }

private:
    SDL_Renderer* renderer;
    SDL_Texture* Item1Texture;
    SDL_Texture* Item2Texture;
    SDL_Texture* Item3Texture;
    SDL_Texture* Item4Texture;
    SDL_Texture* Item5Texture;

    SDL_Rect position;
    SDL_Rect fixedPosition;
    std::vector<bool> itemSpawned;
    std::vector<bool> dropPointPlaced; // Trạng thái droppoint (đã đặt item hay chưa)
    int currentItemIndex;
    bool pickedUp;
};

#endif
