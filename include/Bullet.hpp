#ifndef BULLET_HPP
#define BULLET_HPP
#include "Component.hpp"
#include "Vec2.hpp"

using namespace std;

class Bullet : public Component {
private:
    Vec2 speed;
    float distanceLeft;
    int damage;

public:
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance);
    void Update(float dt);
    void Render();
    bool Is(string type);
    int GetDamage();
};

#endif //BULLET_HPP
