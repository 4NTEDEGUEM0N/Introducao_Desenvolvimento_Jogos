#include "../include/State.hpp"
#include <iostream>

State::State() {
    bool quitRequested = false;
    bg.Open("/home/thiago/CLionProjects/Introducao_Desenvolvimento_Jogos/Recursos/img/Background.png");
    music.Open("/home/thiago/CLionProjects/Introducao_Desenvolvimento_Jogos/Recursos/audio/BGM.wav");
    music.Play();
}

void State::LoadAssets() {}

void State::Update(float dt) {
    quitRequested = SDL_QuitRequested();
}

void State::Render() {
    bg.Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}