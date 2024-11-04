#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>
#include <vector>
#include "Component.hpp"
#include "Rect.hpp"

using namespace std;

class GameObject {
private:
    vector<Component*> components;
    bool isDead;

public:
    GameObject();
    ~GameObject();
    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(string type);
    Rect box;
};


#endif //GAMEOBJECT_HPP
