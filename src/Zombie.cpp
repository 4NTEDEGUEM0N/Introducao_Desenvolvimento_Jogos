#include "../include/Zombie.hpp"
#include "../include/SpriteRenderer.hpp"

Zombie::Zombie(GameObject& associated):Component(associated) {
    hitpoints = 100;
    SpriteRenderer* zmb = new SpriteRenderer(associated, "/home/thiago/CLionProjects/Introducao_Desenvolvimento_Jogos/Recursos/img/Enemy.png", 3,2);
    zmb->SetFrame(2);
    associated.AddComponent(zmb);
}

void Zombie::Damage(int damage) {
    hitpoints -= damage;
    if (hitpoints <= 0) {
        Component* component = associated.GetComponent("SpriteRenderer");
        SpriteRenderer* spriteRenderer = dynamic_cast<SpriteRenderer*>(component);
        spriteRenderer->SetFrame(5);
    }
}

void Zombie::Update(float dt) {
    Damage(1);
}

void Zombie::Render() {}

bool Zombie::Is(string type) {
    return type == "Zombie";
}