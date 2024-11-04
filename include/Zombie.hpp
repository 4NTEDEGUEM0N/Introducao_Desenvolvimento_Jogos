#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include "Component.hpp"
#include "GameObject.hpp"

class Zombie : public Component {
private:
    int hitpoints;

public:
    Zombie(GameObject& associated);
    void Damage(int damage);
    void Update(float dt);
    void Render();
    bool Is(string type);
};

#endif //ZOMBIE_HPP
