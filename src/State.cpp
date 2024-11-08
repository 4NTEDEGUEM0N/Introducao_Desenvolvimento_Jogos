#include "../include/State.hpp"
#include <iostream>

#include "../include/SpriteRenderer.hpp"
#include "../include/Zombie.hpp"
#include "../include/TileMap.hpp"
#include "../include/TileSet.hpp"


State::State() {
    quitRequested = false;

    GameObject* bgObject = new GameObject();
    AddObject(bgObject);
    SpriteRenderer* bg = new SpriteRenderer(*bgObject, "../Recursos/img/Background.png");
    bgObject->AddComponent(bg);

    GameObject* tileMapObject = new GameObject();
    AddObject(tileMapObject);
    tileMapObject->box.X = 0;
    tileMapObject->box.Y = 0;
    TileSet* tileSet = new TileSet("../Recursos/img/Tileset.png", 64, 64);
    TileMap* tileMap = new TileMap(*tileMapObject, "../Recursos/map/map_test.txt", tileSet);
    tileMapObject->AddComponent(tileMap);

    GameObject* zombieObject = new GameObject();
    AddObject(zombieObject);
    Zombie* zmb = new Zombie(*zombieObject, 100);
    zombieObject->box.X = 600;
    zombieObject->box.Y = 450;
    zombieObject->AddComponent(zmb);

    GameObject* zombieObject2 = new GameObject();
    AddObject(zombieObject2);
    Zombie* zmb2 = new Zombie(*zombieObject2, 150);
    zombieObject2->box.X = 500;
    zombieObject2->box.Y = 450;
    zombieObject2->AddComponent(zmb2);

    GameObject* zombieObject3 = new GameObject();
    AddObject(zombieObject3);
    Zombie* zmb3 = new Zombie(*zombieObject3, 200);
    zombieObject3->box.X = 700;
    zombieObject3->box.Y = 450;
    zombieObject3->AddComponent(zmb3);

    music.Open("../Recursos/audio/BGM.wav");
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