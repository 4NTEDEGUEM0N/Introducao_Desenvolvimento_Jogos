#include "../include/State.hpp"
#include <iostream>

#include "../include/SpriteRenderer.hpp"
#include "../include/Zombie.hpp"
#include "../include/TileMap.hpp"
#include "../include/TileSet.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/Character.hpp"
#include "../include/PlayerController.hpp"
#include "../include/Collider.hpp"
#include "../include/Collision.hpp"
#include <algorithm>



State::State() {
    quitRequested = false;
    started = false;

    GameObject* bgObject = new GameObject();
    AddObject(bgObject);
    SpriteRenderer* bg = new SpriteRenderer(*bgObject, "../Recursos/img/Background.png");
    bg->SetCameraFollower(true);
    bgObject->AddComponent(bg);

    GameObject* tileMapObject = new GameObject();
    AddObject(tileMapObject);
    tileMapObject->box.X = 0;
    tileMapObject->box.Y = 0;
    TileSet* tileSet = new TileSet("../Recursos/img/Tileset.png", 64, 64);
    TileMap* tileMap = new TileMap(*tileMapObject, "../Recursos/map/map.txt", tileSet);
    tileMapObject->AddComponent(tileMap);

    music.Open("../Recursos/audio/BGM.wav");
    music.Play();

    GameObject* characterObject = new GameObject();
    characterObject->box.X = 1280;
    characterObject->box.Y = 1280;
    AddObject(characterObject);
    Character* character = new Character(*characterObject, "../Recursos/img/Player.png");
    Camera::Follow(characterObject);
    characterObject->AddComponent(character);
    PlayerController* playerController = new PlayerController(*characterObject);
    characterObject->AddComponent(playerController);

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

    for(int i = 0; i < objectArray.size(); i++) {
        Collider* colliderA = dynamic_cast<Collider*>(objectArray[i]->GetComponent("Collider"));
        if (colliderA != nullptr) {
            for (int j = i + 1; j < objectArray.size(); j++) {
                Collider* colliderB = dynamic_cast<Collider*>(objectArray[j]->GetComponent("Collider"));
                if (colliderB != nullptr) {
                    bool collision = Collision::IsColliding(colliderA->box, colliderB->box, (objectArray[i]->angleDeg * M_PI)/180, (objectArray[j]->angleDeg * M_PI)/180);
                    if (collision) {
                        /*cerr << "BOX A" << endl;
                        cerr << "X: " << colliderA->box.GetX() << endl;
                        cerr << "Y: " << colliderA->box.GetY() << endl;
                        cerr << "W: " << colliderA->box.GetW() << endl;
                        cerr << "H: " << colliderA->box.GetH() << endl;
                        cerr << "BOX B" << endl;
                        cerr << "X: " << colliderB->box.GetX() << endl;
                        cerr << "Y: " << colliderB->box.GetY() << endl;
                        cerr << "W: " << colliderB->box.GetW() << endl;
                        cerr << "H: " << colliderB->box.GetH() << endl; */
                        objectArray[i]->NotifyCollision(*objectArray[j]);
                        objectArray[j]->NotifyCollision(*objectArray[i]);
                    }
                }
            }
        }
    }

    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
    } else {
        quitRequested = InputManager::GetInstance().QuitRequested();
    }

    if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
        GameObject* zombieObject = new GameObject();
        AddObject(zombieObject);
        Zombie* zmb = new Zombie(*zombieObject, 100);
        zombieObject->box.X = InputManager::GetInstance().GetMouseX() + Camera::pos.GetX();
        zombieObject->box.Y = InputManager::GetInstance().GetMouseY() + Camera::pos.GetY();
        zombieObject->AddComponent(zmb);
    }

    Camera::Update(dt);
}

bool Y_Sort(shared_ptr<GameObject> a, shared_ptr<GameObject> b) {
    return a->box.Y < b->box.Y;
}
void State::Render() {
    sort(objectArray.begin(), objectArray.end(), Y_Sort);
    for (int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

weak_ptr<GameObject> State::AddObject(GameObject* go) {
    shared_ptr<GameObject> goPtr(go);
    objectArray.push_back(goPtr);

    if (started) {
        go->Start();
    }

    return weak_ptr<GameObject>(goPtr);
}

void State::Start() {
    LoadAssets();

    for (int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }

    started = true;
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for (int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i].get() == go) {
            return weak_ptr<GameObject>(objectArray[i]);
        }
    }

    return weak_ptr<GameObject>();
}