#ifndef DROPPOINT_H
#define DROPPOINT_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>

class DropImage {
public:
    DropImage();
    ~DropImage();

    bool load(SDL_Renderer* renderer, const std::string& path);
    void render(SDL_Renderer* renderer, const SDL_Rect& camera);
    void cleanup();

    void setVisible(bool v) { visible = v; }

private:
    SDL_Texture* texture;
    int width, height;
    bool visible;
};

class DropPointManager {
public:
    bool loadImages(SDL_Renderer* renderer, const std::vector<std::string>& imagePaths);
    void render(SDL_Renderer* renderer, const SDL_Rect& camera);
    void cleanup();

private:
    std::vector<DropImage> images;
};

#endif
