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
    Music music;
    bool quitRequested;
    vector<shared_ptr<GameObject>> objectArray;
    bool started;

public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
    weak_ptr<GameObject> AddObject(GameObject* go);
    weak_ptr<GameObject> GetObjectPtr(GameObject* go);
    void Start();
};


#endif //STATE_HPP
