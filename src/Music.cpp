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
        Mix_VolumeMusic(32);
        bool mix_playmusic = Mix_PlayMusic(music, times);
        if (mix_playmusic == -1) {
            cerr << "Erro - Mix_PlayMusic: " << SDL_GetError() << endl;
            exit(1);
        }
    }
}

void Music::Stop(int msToStop) {
    bool mix_fadeoutmusic = Mix_FadeOutMusic(msToStop);
    if (mix_fadeoutmusic == 0) {
        cerr << "Erro - Mix_FadeOutMusic: " << SDL_GetError() << endl;
        exit(1);
    }
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
        Stop();
        Mix_FreeMusic(music);
        music = nullptr;
    }
}