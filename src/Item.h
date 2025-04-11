#ifndef ITEM_H
#define ITEM_H

#include <SDL.h>
#include <SDL_image.h>

class Item {
private:
    SDL_Rect rect;       // Vị trí và kích thước của Item
    SDL_Texture* texture; // Ảnh của Item

public:
    Item(SDL_Renderer* renderer, const char* imagePath, int x, int y, int w, int h);
    Item(int x, int y, int w, int h);
    ~Item();

    SDL_Rect getRect() const { return rect; } // Lấy vùng chữ nhật của Item
    void render(SDL_Renderer* renderer);
};

#endif
