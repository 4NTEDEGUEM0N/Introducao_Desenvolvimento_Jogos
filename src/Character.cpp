#include "../include/Character.hpp"

#include <iostream>

#include "../include/SpriteRenderer.hpp"
#include "../include/Animator.hpp"
#include "../include/Gun.hpp"
#include "../include/Game.hpp"

Character* Character::player = nullptr;

Character::Character(GameObject& associated, string sprite) : Component(associated) {
    gun.reset();
    taskQueue = queue<Command>();
    speed = Vec2(0, 0);
    linearSpeed = 200;
    hp = 100;
    deathTimer = Timer();
    dead = false;

    SpriteRenderer* character = new SpriteRenderer(associated, sprite, 3, 4);
    associated.AddComponent(character);

    Animator* animator = new Animator(associated);
    animator->AddAnimation("idle", Animation(6, 9, 0.2));
    animator->AddAnimation("walking", Animation(0, 5, 0.2));
    animator->AddAnimation("dead", Animation(10, 11, 0.5));
    animator->SetAnimation("idle");
    associated.AddComponent(animator);
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
    while(!taskQueue.empty()) {
        Command task = taskQueue.front();
        taskQueue.pop();

        if (task.type == Command::MOVE) {
            Vec2 direction = task.pos;
            direction = direction.normalize();
            speed = direction * linearSpeed;

            associated.box = associated.box + (speed * dt);
        } else if (task.type == Command::SHOOT) {
            Component* component = gun.lock()->GetComponent("Gun");
            Gun* gunCpt = dynamic_cast<Gun*>(component);
            gunCpt->Shot(task.pos);
        }

        if (hp <= 0 && !dead) {
            Component* component = associated.GetComponent("Animator");
            Animator* animator = dynamic_cast<Animator*>(component);
            animator->SetAnimation("dead");
            dead = true;
            deathTimer.Restart();
        }

        if (task.type == Command::MOVE && hp > 0) {
            Component* component = associated.GetComponent("Animator");
            Animator* animator = dynamic_cast<Animator*>(component);
            animator->SetAnimation("walking");
        }

        deathTimer.Update(dt);
        if (dead && deathTimer.Get() > 5) {
            associated.RequestDelete();
        }

        if (task.type != Command::MOVE) {
            Component* component = associated.GetComponent("Animator");
            Animator* animator = dynamic_cast<Animator*>(component);
            animator->SetAnimation("idle");
        }
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


