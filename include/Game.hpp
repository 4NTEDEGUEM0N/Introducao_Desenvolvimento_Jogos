#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include "State.hpp"
#include <string>

using namespace std;

class Game {
private:
    static Game* instance;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    State* state = nullptr;
    Game(string title, int width, int height);
    int frameStart = 0;
    float dt = 0;
    void CalculateDeltaTime();
public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
    static void Quit();
    float GetDeltaTime();
};

#endif //GAME_HPP
