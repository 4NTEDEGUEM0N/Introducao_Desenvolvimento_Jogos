#include "../include/Bullet.hpp"

#include <iostream>

#include "../include/SpriteRenderer.hpp"
#include "../include/GameObject.hpp"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance) : Component(associated) {
    SpriteRenderer* spriteRenderer = new SpriteRenderer(associated, "../Recursos/img/Bullet.png");
    associated.AddComponent(spriteRenderer);

    this->speed = Vec2(1, 0).rotate(angle) * speed;
    distanceLeft = maxDistance;
    this->damage = damage;
}

void Bullet::Update(float dt) {
    associated.box = associated.box + speed * dt;
    distanceLeft -= speed.magnitude() * dt;

    if (distanceLeft <= 0) {
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

bool Bullet::Is(string type) {
    return type == "Bullet";
}

int Bullet::GetDamage() {
    return damage;
}
