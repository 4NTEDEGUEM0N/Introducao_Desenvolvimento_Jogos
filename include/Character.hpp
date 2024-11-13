#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <memory>
#include <queue>

#include "Component.hpp"
#include "Timer.hpp"
#include "Vec2.hpp"

using namespace std;

class Character : public Component {
public:
    class Command {
    public:
        enum CommandType {
            MOVE,
            SHOOT
        };
        CommandType type;
        Vec2 pos;

        Command(CommandType type, float x, float y);

    };

private:
    weak_ptr<GameObject> gun;
    queue<Command> taskQueue;
    Vec2 speed;
    float linearSpeed;
    int hp;
    Timer deathTimer;
    bool dead;

public:
    static Character* player;

    Character(GameObject& associated, string sprite);
    ~Character();
    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);

    void Issue(Command task);


};

#endif //CHARACTER_HPP
