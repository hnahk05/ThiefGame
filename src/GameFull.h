#ifndef GAMEFULL_H
#define GAMEFULL_H

#include <SDL.h>
#include "Graphics.h"
#include "Thief.h"
#include "House.h"
#include "Item.h"
#include "DropPoint.h"

class GameFull {
private:
    bool running;
    Graphics graphics;
    Thief* thief;
    House house;
    std::vector<Item> items;
    std::vector<DropPoint> dropPoints;
    int dogAlert;

public:
    GameFull();
    ~GameFull() {
        if (thief) {
            delete thief;
            thief = nullptr;
        }
    }
    bool init();
    void run();
    void handleEvents();
    void update();
    void render();
    void clean();
};

#endif
