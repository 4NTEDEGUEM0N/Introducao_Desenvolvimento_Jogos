#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

Sprite::Sprite() {
    texture = nullptr;
}

Sprite::Sprite(string file, int frame_count_w, int frame_count_h) {
    texture = nullptr;
    SetFrameCount(frame_count_w, frame_count_h);
    Open(file);
}

Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Sprite::Open(string file) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture == nullptr) {
        cerr << "Erro - IMG_LoadTexture: " << SDL_GetError() << endl;
        exit(1);
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y, int w, int h) {
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = w;
    dstRect.h = h;

    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
}

int Sprite::GetWidth() {
    return width / frameCountW;
}

int Sprite::GetHeight() {
    return height / frameCountH;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}

void Sprite::SetFrame(int frame) {
    if (frame < 0 || frame >= (frameCountW * frameCountH)) {
        cerr << "Erro - Frame inválido: " << frame << endl;
        exit(1);
    }

    int w = width / frameCountW;
    int h = height / frameCountH;

    int x = (frame % frameCountW) * w;
    int y = (frame / frameCountW) * h;

    if (x < 0 || y < 0 || x + w > width || y + h > height) {
        cerr << "Erro - Clip inválido: x=" << x << ", y=" << y << ", width=" << w << ", height=" << h << endl;
        exit(1);
    }

    SetClip(x, y, w, h);
}

void Sprite::SetFrameCount(int frame_count_w, int frame_count_h) {
    frameCountW = frame_count_w;
    frameCountH = frame_count_h;
}
