#ifndef HOUSE_H
#define HOUSE_H

#include <vector>
#include <SDL.h>

class House {
private:
    std::vector<SDL_Rect> furniture; // Các đồ đạc trong nhà

public:
    House();
    void loadHouse(); // Tạo đồ đạc
    bool checkCollision(SDL_Rect &rect);
    void render(SDL_Renderer *renderer);
};

#endif
