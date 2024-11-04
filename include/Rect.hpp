#ifndef RECT_HPP
#define RECT_HPP

#include <string>
#include "Vec2.hpp"

using namespace std;

class Rect {
private:
    float X;
    float Y;
    float W;
    float H;

public:
    Rect(float x = 0, float y = 0, float w = 0, float h = 0);
    float GetX();
    float GetY();
    float GetW();
    float GetH();
    Rect operator+(Vec2& vector);
    Vec2 center();
    static float distance(Rect& rect1, Rect& rect2);
    bool contains(Vec2& vector);
    Rect& operator=(Rect& rect2);
};



#endif //RECT_HPP