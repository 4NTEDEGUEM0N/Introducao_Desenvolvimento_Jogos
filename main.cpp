#include "include/Game.hpp"
#include <iostream>

#include "include/StageState.hpp"

int main (int argc, char** argv) {
    Game& game = Game::GetInstance();
    StageState* teste = new StageState();
    game.Push(teste);
    game.Run();
    Game::Quit();

    return 0;
}
