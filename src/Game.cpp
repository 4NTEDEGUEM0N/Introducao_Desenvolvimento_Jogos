#include "../include/Game.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "../include/Resources.hpp"
#include "../include/InputManager.hpp"

using namespace std;

Game* Game::instance = nullptr;

Game& Game::GetInstance(){
    if(instance != nullptr){
        return *instance;
    }
    instance = new Game("Thiago - 200073303", 1200, 900);
    return *instance;
}

Game::Game(string title, int width, int height){
    if(instance != nullptr){
        cerr << ("Erro: Instância já existe") << endl;
        exit(1);
    }
    instance = this;

    int sdl_init = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if (sdl_init != 0){
        cerr << "Erro - SDL_Init: " << SDL_GetError() << endl;
        exit(1);
    }

    int img_init = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    if (img_init != (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)) {
        cerr << "Erro - IMG_Init: "<< SDL_GetError() << endl;
        exit(1);
    }

    int mix_init = Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    if (mix_init != (MIX_INIT_MP3 | MIX_INIT_OGG)) {
        cerr << "Erro - Mix_Init: "<< SDL_GetError() << endl;
        exit(1);
    }

    int mix_openaudio = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    if (mix_openaudio != 0) {
        cerr << "Erro - Mix_OpenAudio: "<< SDL_GetError() << endl;
        exit(1);
    }
    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr) {
        cerr << "Erro - SDL_CreateWindow: "<< SDL_GetError() << endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cerr << "Erro - SDL_CreateRenderer: "<< SDL_GetError() << endl;
        exit(1);
    }
}

Game::~Game(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

State& Game::GetState(){
    return *state;
}

SDL_Renderer* Game::GetRenderer(){
    return renderer;
}

void Game::Run(){
    state = new State();
    state->Start();
    while(!state->QuitRequested()){
        CalculateDeltaTime();
        InputManager::GetInstance().Update();
        state->Update(dt);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(15);
    }
    delete state;
    state = nullptr;
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}

void Game::Quit() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

void Game::CalculateDeltaTime(){
    int newFrameStart = SDL_GetTicks();
    dt = (newFrameStart - frameStart) / 1000.0;
    frameStart = newFrameStart;
}

float Game::GetDeltaTime(){
    return dt;
}

