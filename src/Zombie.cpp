#include "../include/Zombie.hpp"
#include "../include/SpriteRenderer.hpp"
#include "../include/Animator.hpp"
#include <iostream>

Zombie::Zombie(GameObject& associated, int hp):Component(associated), deathSound("../Recursos/audio/Dead.wav") {
    hitpoints = hp;
    hasPlayedDeathSound = false;

    SpriteRenderer* zmb = new SpriteRenderer(associated, "../Recursos/img/Enemy.png", 3,2);
    associated.AddComponent(zmb);

    Animator *animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 3, 10));
    animator->AddAnimation("dead", Animation(5, 5, 0));
    animator->SetAnimation("walking");
    associated.AddComponent(animator);


}

void Zombie::Damage(int damage) {
    hitpoints -= damage;
    if (hitpoints <= 0) {
        Component* component = associated.GetComponent("Animator");
        Animator* animator = dynamic_cast<Animator*>(component);
        animator->SetAnimation("dead");

        if (!hasPlayedDeathSound) {
            hasPlayedDeathSound = true;
            deathSound.Play(1);
        }
    }
}

void Zombie::Update(float dt) {
    Damage(1);
}

void Zombie::Render() {}

bool Zombie::Is(string type) {
    return type == "Zombie";
}