#include "Item.h"
#include <iostream>
using namespace std;
#include <defs.h>

Item::Item(SDL_Renderer* renderer, int fixedX, int fixedY)
    : renderer(renderer), Item1Texture(nullptr), Item2Texture(nullptr),
      Item3Texture(nullptr), Item4Texture(nullptr), Item5Texture(nullptr),
      currentItemIndex(-1) {

    // Khởi tạo ngẫu nhiên
    srand(time(0));

    // Tải 5 ảnh item
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

    if (!Item1Texture || !Item2Texture || !Item3Texture || !Item4Texture || !Item5Texture) return;

    // Khởi tạo trạng thái của các item (chưa xuất hiện)
    itemSpawned = vector<bool>(5, false); // 5 items, tất cả chưa xuất hiện

    // Đặt vị trí cố định cho item
    fixedPosition = {fixedX, fixedY, ITEM_SIZE, ITEM_SIZE};
}

Item::~Item() {
    if (Item1Texture) SDL_DestroyTexture(Item1Texture);
    if (Item2Texture) SDL_DestroyTexture(Item2Texture);
    if (Item3Texture) SDL_DestroyTexture(Item3Texture);
    if (Item4Texture) SDL_DestroyTexture(Item4Texture);
    if (Item5Texture) SDL_DestroyTexture(Item5Texture);
}

void Item::spawnItem() {
    // Kiểm tra xem còn item nào chưa xuất hiện không
    bool allSpawned = true;
    for (bool spawned : itemSpawned) {
        if (!spawned) {
            allSpawned = false;
            break;
        }
    }
    if (allSpawned) {
        currentItemIndex = -1; // Không còn item nào để hiển thị
        printf("Tất cả item đã xuất hiện!\n");
        return;
    }

    // Chọn ngẫu nhiên một item chưa xuất hiện
    int itemIndex;
    do {
        itemIndex = rand() % 5; // Chọn ngẫu nhiên từ 0 đến 4
    } while (itemSpawned[itemIndex]); // Lặp lại nếu item đã xuất hiện

    // Đặt item hiện tại
    currentItemIndex = itemIndex;

    // Đánh dấu item đã xuất hiện
    itemSpawned[itemIndex] = true;
}

void Item::render(SDL_Renderer* renderer, int cameraX, int cameraY) {
    // Nếu không có item nào đang hiển thị, không vẽ gì
    if (currentItemIndex == -1) return;

    // Vẽ item tại vị trí cố định, điều chỉnh theo camera
    SDL_Rect renderRect = {
        fixedPosition.x - cameraX,
        fixedPosition.y - cameraY,
        ITEM_SIZE,
        ITEM_SIZE
    };

    // Vẽ texture tương ứng với item hiện tại
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
