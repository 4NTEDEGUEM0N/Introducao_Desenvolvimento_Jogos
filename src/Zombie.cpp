#include "../include/Zombie.hpp"
#include "../include/SpriteRenderer.hpp"
#include "../include/Animator.hpp"
#include "../include/Camera.hpp"
#include <iostream>

#include "../include/InputManager.hpp"

Zombie::Zombie(GameObject& associated, int hp):Component(associated), deathSound("../Recursos/audio/Dead.wav"), hitSound("../Recursos/audio/Hit0.wav") {
    hitpoints = hp;
    hasPlayedDeathSound = false;
    hit = false;

    SpriteRenderer* zmb = new SpriteRenderer(associated, "../Recursos/img/Enemy.png", 3,2);
    associated.AddComponent(zmb);

    Animator *animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 3, 0.2));
    animator->AddAnimation("dead", Animation(5, 5, 0));
    animator->AddAnimation("hit", Animation(4, 4, 0));
    animator->SetAnimation("walking");
    associated.AddComponent(animator);


}

void Zombie::Damage(int damage) {
    hitpoints -= damage;
    if (hitpoints <= 0 && !hasPlayedDeathSound) {
        Component* component = associated.GetComponent("Animator");
        Animator* animator = dynamic_cast<Animator*>(component);
        animator->SetAnimation("dead");

        hasPlayedDeathSound = true;
        deathSound.Play(1);
        deathTimer.Restart();

    } else if (hitpoints > 0 && !hasPlayedDeathSound) {
        hit = true;
        hitTimer.Restart();
        Component* component = associated.GetComponent("Animator");
        Animator* animator = dynamic_cast<Animator*>(component);
        animator->SetAnimation("hit");
    }
}

void Zombie::Update(float dt) {
    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
        int mouseX = InputManager::GetInstance().GetMouseX();
        int mouseY = InputManager::GetInstance().GetMouseY();
        float cameraX = Camera::pos.GetX();
        float cameraY = Camera::pos.GetY();
        Vec2 mousePos = Vec2(mouseX + cameraX, mouseY + cameraY);

        if (associated.box.contains(mousePos)) {
            hitSound.Play(1);
            Damage(25);
        }
    }
    hitTimer.Update(dt);
    if (hit && hitTimer.Get() > 0.5 && hitpoints > 0) {
        hit = false;
        Component* component = associated.GetComponent("Animator");
        Animator* animator = dynamic_cast<Animator*>(component);
        animator->SetAnimation("walking");
    }

    deathTimer.Update(dt);
    if (hitpoints <= 0 && deathTimer.Get() > 5) {
        associated.RequestDelete();
    }
}

void Zombie::Render() {}

bool Zombie::Is(string type) {
    return type == "Zombie";
}