#include "../include/Music.hpp"
#include <iostream>

using namespace std;

Music::Music() {
    music = nullptr;
}

Music::Music(string file) {
    music = nullptr;
    Open(file);
}

void Music::Play(int times) {
    if (music != nullptr) {
        Mix_VolumeMusic(1);
        Mix_PlayMusic(music, times);
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file) {
    if (music != nullptr) {
        Mix_FreeMusic(music);
    }

    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        cerr << "Erro - Mix_LoadMUS: " << SDL_GetError() << endl;
        exit(1);
    }
}

bool Music::IsOpen() {
    return music != nullptr;
}

Music::~Music() {
    if (music != nullptr) {
        Mix_FreeMusic(music);
    }
}