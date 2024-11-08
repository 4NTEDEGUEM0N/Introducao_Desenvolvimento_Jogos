#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include "Component.hpp"
#include "GameObject.hpp"
#include "Sound.hpp"

class Zombie : public Component {
private:
    int hitpoints;
    Sound deathSound;
    bool hasPlayedDeathSound;

public:
    Zombie(GameObject& associated);
    void Damage(int damage);
    void Update(float dt);
    void Render();
    bool Is(string type);
};

#endif //ZOMBIE_HPP
