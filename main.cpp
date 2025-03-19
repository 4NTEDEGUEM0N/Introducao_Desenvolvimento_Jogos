#include "include/Game.hpp"
#include <iostream>

#include "include/StageState.hpp"
#include "include/TitleState.hpp"

int main (int argc, char** argv) {
    Game& game = Game::GetInstance();
    //StageState* teste = new StageState();
    TitleState* tileState = new TitleState();
    game.Push(tileState);
    game.Run();
    Game::Quit();

    return 0;
}
