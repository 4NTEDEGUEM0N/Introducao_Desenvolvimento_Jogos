#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>
class GameObject; //#include "GameObject.hpp"

using namespace std;

class Component {
protected:
    GameObject& associated;

public:
    Component(GameObject& associated);
    virtual ~Component();

    void virtual Update(float dt) = 0;
    void virtual Render() = 0;
    bool virtual Is(string type) = 0;
};

#endif //COMPONENT_HPP
