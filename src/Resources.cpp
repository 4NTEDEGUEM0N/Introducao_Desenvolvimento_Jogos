#include "../include/Resources.hpp"
#include "../include/Game.hpp"

#include <iostream>
#include <SDL_image.h>

using namespace std;

unordered_map<string, SDL_Texture*> Resources::imageTable;
unordered_map<string, Mix_Music*> Resources::musicTable;
unordered_map<string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(string file) {
    SDL_Texture* texture = nullptr;
    auto search = imageTable.find(file);
    if (search == imageTable.end()) {
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        if (texture == nullptr) {
            cerr << "Erro - IMG_LoadTexture: " << SDL_GetError() << endl;
            exit(1);
        }
        imageTable[file] = texture;
    } else {
        texture = search->second;
    }

    return texture;
}

void Resources::ClearImages() {
    for (auto it = imageTable.begin(); it != imageTable.end(); it++) {
        SDL_DestroyTexture(it->second);
    }
    imageTable.clear();
}

Mix_Music* Resources::GetMusic(string file) {
    Mix_Music* music = nullptr;
    auto search = musicTable.find(file);
    if (search == musicTable.end()) {
        music = Mix_LoadMUS(file.c_str());
        if (music == nullptr) {
            cerr << "Erro - Mix_LoadMUS: " << SDL_GetError() << endl;
            exit(1);
        }
        musicTable[file] = music;
    } else {
        music = search->second;
    }

    return music;
}

void Resources::ClearMusics() {
    for (auto it = musicTable.begin(); it != musicTable.end(); it++) {
        Mix_FreeMusic(it->second);
    }
    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(string file) {
    Mix_Chunk* chunk = nullptr;
    auto search = soundTable.find(file);
    if (search == soundTable.end()) {
        chunk = Mix_LoadWAV(file.c_str());
        if (chunk == nullptr) {
            cerr << "Erro - Mix_LoadWAV: " << SDL_GetError() << endl;
            exit(1);
        }
        soundTable[file] = chunk;
    } else {
        chunk = search->second;
    }

    return chunk;
}

void Resources::ClearSounds() {
    for (auto it = soundTable.begin(); it != soundTable.end(); it++) {
        Mix_FreeChunk(it->second);
    }
    soundTable.clear();
}

