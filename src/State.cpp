#include "../include/State.hpp"
#include <iostream>

#include "../include/SpriteRenderer.hpp"

State::State() {
    quitRequested = false;

    GameObject* go = new GameObject();
    SpriteRenderer* bg = new SpriteRenderer(*go, "/home/thiago/CLionProjects/Introducao_Desenvolvimento_Jogos/Recursos/img/Background.png");
    go->AddComponent(bg);
    objectArray.emplace_back(go);

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
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::AddObject(GameObject* go) {
    objectArray.emplace_back(go);
}