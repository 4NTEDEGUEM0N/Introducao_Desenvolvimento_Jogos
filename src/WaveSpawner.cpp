#include "../include/WaveSpawner.hpp"
#include "../include/Game.hpp"
#include "../include/State.hpp"
#include "../include/Zombie.hpp"
#include "iostream"

WaveSpawner::WaveSpawner(GameObject &associated): Component(associated) {
    zombieCounter = 0;
    zombieCooldownTimer.Restart();
    currentWave = 0;
    waves.emplace_back(5,5);
    waves.emplace_back(10,2);
    waves.emplace_back(15,3);
}

void WaveSpawner::Update(float dt) {
    zombieCooldownTimer.Update(dt);


    if (zombieCounter < waves.begin()->zombies && zombieCooldownTimer.Get() > waves.begin()->cooldown) {
        State& state = Game::GetInstance().GetState();
        GameObject* zombieObject = new GameObject();
        state.AddObject(zombieObject);
        Zombie* zmb = new Zombie(*zombieObject, 100);
        int waveX = 576 + rand()%(1984 - 576 + 1);
        int waveY = 448 + rand()%(2112 - 448 + 1);
        zombieObject->box.X = waveX;
        zombieObject->box.Y = waveY;
        zombieObject->AddComponent(zmb);

        zombieCounter +=1;
        zombieCooldownTimer.Restart();
    } else if (zombieCounter == waves.begin()->zombies && Zombie::zombieCounter == 0) {
        waves.erase(waves.begin());
        zombieCounter = 0;
        currentWave += 1;
    }

    if (waves.begin() == waves.end()) {
        associated.RequestDelete();
    }
}

void WaveSpawner::Render() {}

bool WaveSpawner::Is(string type) {
    return type == "WaveSpawner";
}



