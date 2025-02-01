#include "../include/Collider.hpp"

#include <math.h>

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset): Component(associated) {
    this->scale = scale;
    this->offset = offset;
}

void Collider::Update(float dt) {
    this->box.W = associated.box.GetW() * scale.GetX();
    this->box.H = associated.box.GetH() * scale.GetY();

    double angleRad = (associated.angleDeg * M_PI)/180;
    Vec2 newCenter = offset.rotate(angleRad) + associated.box.center();
    box.X = newCenter.GetX() - box.GetW() / 2;
    box.Y = newCenter.GetY() - box.GetH() / 2;
}

void Collider::Render() {};

bool Collider::Is(string type) {
    return type == "Collider";
}

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}





