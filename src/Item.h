#ifndef ITEM_H
#define ITEM_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <cstdlib>
#include <ctime>

class Item {
public:
    Item(SDL_Renderer* renderer, int fixedX, int fixedY); // Truyền vị trí cố định
    ~Item();
    void spawnItem(); // Chọn ngẫu nhiên một item và hiển thị tại vị trí cố định
    void render(SDL_Renderer* renderer, int cameraX, int cameraY); // Vẽ item

private:
    SDL_Renderer* renderer;
    SDL_Texture* Item1Texture;
    SDL_Texture* Item2Texture;
    SDL_Texture* Item3Texture;
    SDL_Texture* Item4Texture;
    SDL_Texture* Item5Texture;

    SDL_Rect fixedPosition; // Vị trí cố định của item
    std::vector<bool> itemSpawned; // Trạng thái của từng item (đã xuất hiện hay chưa)
    int currentItemIndex; // Chỉ số của item hiện tại (-1 nếu chưa có item)
};

#endif
