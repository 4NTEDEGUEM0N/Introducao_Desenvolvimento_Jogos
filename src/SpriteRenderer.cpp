#include "../include/SpriteRenderer.hpp"

#include "../include/GameObject.hpp"

SpriteRenderer::SpriteRenderer(GameObject& associated):Component(associated) {}

SpriteRenderer::SpriteRenderer(GameObject& associated, string file, int frame_count_w, int frame_count_h)
                                :Component(associated), sprite(file, frame_count_w, frame_count_h) {
    associated.box.W = sprite.GetWidth();
    associated.box.H = sprite.GetHeight();
    sprite.SetFrame(0);
}

void SpriteRenderer::SetFrameCount(int frame_count_w, int frame_count_h) {
    sprite.SetFrameCount(frame_count_w, frame_count_h);
}

void SpriteRenderer::Open(string file) {
    sprite.Open(file);
    associated.box.W = sprite.GetWidth();
    associated.box.H = sprite.GetHeight();
}

void SpriteRenderer::SetFrame(int frame) {
    sprite.SetFrame(frame);
}

void SpriteRenderer::Update(float dt) {}

void SpriteRenderer::Render() {
    sprite.Render(associated.box.X, associated.box.Y, associated.box.W, associated.box.H);
}

bool SpriteRenderer::Is(string type) {
    return type == "SpriteRenderer";
}
