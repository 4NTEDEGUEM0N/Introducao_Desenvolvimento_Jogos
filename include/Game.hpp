#ifndef GAME_HPP
#define GAME_HPP

#include <stack>
#include <SDL2/SDL.h>
#include "State.hpp"
#include <string>

using namespace std;
/*
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
}; */

class Game {
public:
    Game(string title, int width, int height);
    ~Game();
    static void Quit();

    static Game& GetInstance();
    SDL_Renderer* GetRenderer();
    State& GetState();

    void Push(State* state);

    void Run();

    float GetDeltaTime();

private:
    void CalculateDeltaTime();

    int frameStart;
    float dt;

    static Game* instance;

    State* storedState;
    SDL_Window* window;
    SDL_Renderer* renderer;
    stack<unique_ptr<State>>stateStack;

};

#endif //GAME_HPP
