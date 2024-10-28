#ifndef STATE_HPP
#define STATE_HPP

#include <SDL2/SDL.h>
#include "Sprite.hpp"
#include "Music.hpp"
using namespace std;

class State {
private:
    Sprite bg;
    Music music;
    bool quitRequested;

public:
    State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
};


#endif //STATE_HPP
