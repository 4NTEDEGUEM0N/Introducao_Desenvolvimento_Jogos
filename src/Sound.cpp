#include "../include/Sound.hpp"

#include <iostream>

Sound::Sound() {
    chunk = nullptr;
}

Sound::Sound(string file): Sound() {
    Open(file);
}

void Sound::Play(int times) {
    channel = Mix_PlayChannel(-1, chunk, times - 1);
    if (channel == -1) {
        cerr << "Erro - Mix_PlayChannel: " << SDL_GetError() << endl;
        exit(1);
    }
    Mix_Volume(channel, 32);
}

void Sound::Stop() {
    if (chunk != nullptr) {
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(string file) {
    chunk = Mix_LoadWAV(file.c_str());
    if (chunk == nullptr) {
        cerr << "Erro - Mix_LoadWAV: " << SDL_GetError() << endl;
        exit(1);
    }
}

Sound::~Sound() {
    if (chunk != nullptr) {
        Mix_HaltChannel(channel);
        Mix_FreeChunk(chunk);
    }
}

bool Sound::IsOpen() {
    return chunk != nullptr;
}
