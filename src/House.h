#ifndef HOUSE_H
#define HOUSE_H

#include <vector>
#include <SDL.h>

class House {
private:
    std::vector<SDL_Rect> furniture; // Các đồ đạc trong nhà

public:
    House();
    House(int x, int y, int width, int height);
    void loadHouse(); // Tạo đồ đạc
    bool checkCollision(SDL_Rect &rect);
    void render(SDL_Renderer *renderer);
    SDL_Rect getRect() const;
};

#endif
