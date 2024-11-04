#ifndef STATE_HPP
#define STATE_HPP

#include <memory>
#include <SDL2/SDL.h>
#include "Sprite.hpp"
#include "Music.hpp"
#include "GameObject.hpp"
using namespace std;

class State {
private:
    Sprite bg;
    Music music;
    bool quitRequested;
    vector<unique_ptr<GameObject>> objectArray;

public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void AddObject(GameObject* go);
};


#endif //STATE_HPP
