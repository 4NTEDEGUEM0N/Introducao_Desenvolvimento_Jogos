#include "../include/Character.hpp"

#include <iostream>

#include "../include/SpriteRenderer.hpp"
#include "../include/Animator.hpp"
#include "../include/Collider.hpp"
#include "../include/Gun.hpp"
#include "../include/Game.hpp"
#include "../include/Zombie.hpp"
#include "../include/Camera.hpp"

Character* Character::player = nullptr;

Character::Character(GameObject& associated, string sprite) : Component(associated), deathSound("../Recursos/audio/Dead.wav"), hitSound("../Recursos/audio/Hit1.wav") {
    gun.reset();
    taskQueue = queue<Command>();
    speed = Vec2(0, 0);
    linearSpeed = 200;
    hp = 100;
    deathTimer = Timer();
    dead = false;
    damageCooldown = Timer();

    SpriteRenderer* character = new SpriteRenderer(associated, sprite, 3, 4);
    associated.AddComponent(character);

    Animator* animator = new Animator(associated);
    animator->AddAnimation("idle", Animation(6, 9, 0.2));
    animator->AddAnimation("idleLeft", Animation(6, 9, 0.2, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("walkingRight", Animation(0, 5, 0.2));
    animator->AddAnimation("walkingLeft", Animation(0, 5, 0.2, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("dead", Animation(10, 11, 0.5));

    animator->SetAnimation("idle");
    associated.AddComponent(animator);

    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);
}

Character::~Character() {
    if (player == this) {
        player = nullptr;
    }
}

void Character::Start() {
    State& state = Game::GetInstance().GetState();

    GameObject* gunObject = new GameObject();
    weak_ptr<GameObject> gunObjectPtr = state.AddObject(gunObject);

    Gun* gunCpt = new Gun(*gunObject, weak_ptr<GameObject>(state.GetObjectPtr(&associated)));
    gunObject->AddComponent(gunCpt);

    gun = gunObjectPtr;
}

void Character::Update(float dt) {
    Component* component = associated.GetComponent("Animator");
    Animator* animator = dynamic_cast<Animator*>(component);
    while(!taskQueue.empty()) {
        Command task = taskQueue.front();
        taskQueue.pop();

        if (task.type == Command::MOVE) {
            if (task.pos == Vec2(0,0)) {
                string currentAnimation = animator->GetAnimation();
                if (currentAnimation == "walkingRight")
                    animator->SetAnimation("idle");
                else if (currentAnimation == "walkingLeft")
                    animator->SetAnimation("idleLeft");
            } else {
                Vec2 direction = task.pos;
                direction = direction.normalize();
                speed = direction * linearSpeed;

                associated.box = associated.box + (speed * dt);
            }
        } else if (task.type == Command::SHOOT) {
            Component* component = gun.lock()->GetComponent("Gun");
            Gun* gunCpt = dynamic_cast<Gun*>(component);
            gunCpt->Shot(task.pos);
        }

        if (hp <= 0 && !dead) {
            animator->SetAnimation("dead");
            dead = true;
            deathSound.Play(1);
            deathTimer.Restart();
            Camera::Unfollow();
            Component* playerController = associated.GetComponent("PlayerController");
            if (playerController != nullptr)
                associated.RemoveComponent(playerController);
        }

        if (task.type == Command::MOVE && hp > 0) {
            if (task.pos.GetX() < 0) {
                animator->SetAnimation("walkingLeft");
            } else if (task.pos.GetX() > 0 || task.pos.GetY() != 0) {
                animator->SetAnimation("walkingRight");
            }
        }
        damageCooldown.Update(dt);
    }
    deathTimer.Update(dt);
    if (dead && deathTimer.Get() > 5) {
        associated.RequestDelete();
    }
}

void Character::Render() {}

bool Character::Is(string type) {
    return type == "Character";
}

void Character::Issue(Command task) {
    taskQueue.push(task);
}

Character::Command::Command(CommandType type, float x, float y) {
    this->type = type;
    this->pos = Vec2(x, y);
}

void Character::NotifyCollision(GameObject &other) {
    if (other.GetComponent("Zombie") != nullptr) {
        if (damageCooldown.Get() > 1 && hp > 0) {
            hp -= 25;
            damageCooldown.Restart();
            hitSound.Play(1);
        }
    }
}



