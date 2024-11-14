#include "../include/Gun.hpp"

#include <iostream>

#include "../include/SpriteRenderer.hpp"
#include "../include/Animator.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"

Gun::Gun(GameObject& associated, weak_ptr<GameObject> character) : Component(associated),
                                                                   shotSound("../Recursos/audio/Range.wav"), reloadSound("../Recursos/audio/PumpAction.mp3"), character(character) {
    cdTimer = Timer();
    cooldown = 0;
    angle = 0;
    reloaded = true;

    SpriteRenderer* gun = new SpriteRenderer(associated, "../Recursos/img/Gun.png", 3, 2);
    associated.AddComponent(gun);

    Animator* animator = new Animator(associated);
    animator->AddAnimation("idle", Animation(0, 0, 0));
    animator->AddAnimation("reload", Animation(1, 5, 0.08));
    animator->SetAnimation("idle");
    associated.AddComponent(animator);
}

void Gun::Update(float dt) {
    if (character.expired()) {
        associated.RequestDelete();
        return;
    }
    cerr << cooldown << endl;

    Vec2 character_center = character.lock()->box.center();
    float gunX = character_center.GetX() - associated.box.GetW() / 2;
    float gunY = character_center.GetY() - associated.box.GetH() / 2;
    associated.box.X = gunX;
    associated.box.Y = gunY + 25;

    Vec2 direction = Vec2(1, 0).rotate(angle);
    associated.box = associated.box + direction * 10;

    if (cooldown > 0) {
        cooldown -= dt;
    }

    if (cooldown <= 0 && !reloaded) {
        Animator* animator = dynamic_cast<Animator*>(associated.GetComponent("Animator"));
        animator->SetAnimation("reload");
        reloadSound.Play(1);
        cdTimer.Restart();
        reloaded = true;
    }

    cdTimer.Update(dt);
    if (cdTimer.Get() > 0.5) {
        Animator* animator = dynamic_cast<Animator*>(associated.GetComponent("Animator"));
        animator->SetAnimation("idle");
    }
}

void Gun::Render() {}

bool Gun::Is(string type) {
    return type == "Gun";
}

void Gun::Shot(Vec2 target) {
    if (cooldown > 0) {
        return;
    }

    Vec2 direction = target - associated.box.center();
    direction = direction.normalize();
    angle = direction.angle();

    shotSound.Play(1);
    cooldown = 50;
    cdTimer.Restart();
    reloaded = false;
}


