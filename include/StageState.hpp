#ifndef STAGESTATE_HPP
#define STAGESTATE_HPP

#include "Music.hpp"
#include "State.hpp"
#include "TileSet.hpp"

using namespace std;

class StageState : public State {
private:
    TileSet* tileSet;
    Music backgroundMusic;

public:
    StageState();
    ~StageState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
};


#endif //STAGESTATE_HPP
