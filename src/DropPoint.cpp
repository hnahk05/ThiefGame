/*"assets/droppoint/alcohol_drop.png",
"assets/droppoint/clock_drop.png",
"assets/droppoint/computer_drop.png",
"assets/droppoint/money_drop.png",
"assets/droppoint/phone_drop.png"*/
#include "DropPoint.h"
#include <SDL_log.h>

DropImage::DropImage() : texture(nullptr), width(0), height(0), visible(true) {}

DropImage::~DropImage() {
    cleanup();
}

bool DropImage::load(SDL_Renderer* renderer, const std::string& path) {
    texture = IMG_LoadTexture(renderer, path.c_str());
    if (!texture) {
        SDL_Log("Failed to load %s: %s", path.c_str(), IMG_GetError());
        return false;
    }
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    return true;
}

void DropImage::render(SDL_Renderer* renderer, const SDL_Rect& camera) {
    if (visible && texture) {
        SDL_Rect renderQuad = { -camera.x, -camera.y, width, height };
        SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
    }
}

void DropImage::cleanup() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

bool DropPointManager::loadImages(SDL_Renderer* renderer, const std::vector<std::string>& imagePaths) {
    for (const auto& path : imagePaths) {
        DropImage img;
        if (img.load(renderer, path)) {
            images.push_back(std::move(img));
        } else {
            return false; // stop if any image fails to load
        }
    }
    return true;
}

void DropPointManager::render(SDL_Renderer* renderer, const SDL_Rect& camera) {
    for (auto& img : images) {
        img.render(renderer, camera);
    }
}

void DropPointManager::cleanup() {
    for (auto& img : images) {
        img.cleanup();
    }
    images.clear();
}

