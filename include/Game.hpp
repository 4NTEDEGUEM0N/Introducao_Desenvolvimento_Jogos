#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include "State.hpp"
#include <string>

using namespace std;

class Game {
private:
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
    Game(string title, int width, int height);
public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
};

#endif //GAME_HPP
