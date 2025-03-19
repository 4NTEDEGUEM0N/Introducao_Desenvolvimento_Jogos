#include "../include/TitleState.hpp"

#include <iostream>

#include "../include/InputManager.hpp"
#include "../include/SpriteRenderer.hpp"
#include "../include/StageState.hpp"
#include "../include/Game.hpp"
#include "../include/Camera.hpp"
#include "../include/Text.hpp"

TitleState::TitleState() {
    GameObject* bgObject = new GameObject();
    AddObject(bgObject);
    SpriteRenderer* titleBg = new SpriteRenderer(*bgObject, "../Recursos/img/Title.png");
    titleBg->SetCameraFollower(true);
    bgObject->AddComponent(titleBg);

    GameObject* instructionsObject = new GameObject();
    this->instructionsObject = AddObject(instructionsObject);
    instructionsObject->box.X = 400;
    instructionsObject->box.Y = 450;
    Text* instructionsText = new Text(*instructionsObject, "../Recursos/font/neodgm.ttf", 30, Text::SHADED, "PRESS THE SPACE BAR TO START", {255, 255, 255, 255});
    instructionsObject->AddComponent(instructionsText);
    up = false;
    counter = 0;
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

    counter++;
    if (counter == 50) {
        counter = 1;
        up = !up;
    }
    Text* textCpt = dynamic_cast<Text*>(instructionsObject.lock()->GetComponent("Text"));
    if (up) {
        Uint8 alpha = counter*5;
        textCpt->SetColor({255, 255, 255, alpha});
    } else {
        Uint8 alpha = 255 - counter*5;
        textCpt->SetColor({255, 255, 255, alpha});
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


