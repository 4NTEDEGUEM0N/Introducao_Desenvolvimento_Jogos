#include "../include/State.hpp"
#include <iostream>

State::State() {
    quitRequested = false;
    bg.Open("/home/thiago/CLionProjects/Introducao_Desenvolvimento_Jogos/Recursos/img/Background.png");
    music.Open("/home/thiago/CLionProjects/Introducao_Desenvolvimento_Jogos/Recursos/audio/BGM.wav");
    music.Play();
}

State::~State() {
    objectArray.clear();
}


void State::LoadAssets() {}

void State::Update(float dt) {
    for(int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    for(int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }


    quitRequested = SDL_QuitRequested();
}

void State::Render() {
    for (int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
    }
    bg.Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::AddObject(GameObject* go) {
    objectArray.emplace_back(go);
}