#include "../include/TitleState.hpp"

#include <iostream>

#include "../include/InputManager.hpp"
#include "../include/SpriteRenderer.hpp"
#include "../include/StageState.hpp"
#include "../include/Game.hpp"
#include "../include/Camera.hpp"

TitleState::TitleState() {
    GameObject* titleObjetct = new GameObject();
    AddObject(titleObjetct);
    SpriteRenderer* titleBg = new SpriteRenderer(*titleObjetct, "../Recursos/img/Title.png");
    titleBg->SetCameraFollower(true);
    titleObjetct->AddComponent(titleBg);
}

void TitleState::Update(float dt) {
    UpdateArray(dt);

    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
    } else {
        quitRequested = InputManager::GetInstance().QuitRequested();
    }

    if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
        Game& game = Game::GetInstance();
        StageState* stage = new StageState();
        game.Push(stage);
        //popRequested = true;
    }

    Camera::Update(dt);
}

void TitleState::Render() {
    RenderArray();
}
void TitleState::LoadAssets() {}
void TitleState::Start() {
    StartArray();
}
void TitleState::Pause() {}
void TitleState::Resume() {}
TitleState::~TitleState() = default;


