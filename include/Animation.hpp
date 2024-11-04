#ifndef ANIMATION_HPP
#define ANIMATION_HPP

using namespace std;

class Animation {
public:
    int frameStart;
    int frameEnd;
    float frameTime;

    Animation(int frame_start=0, int frame_end=0, float frame_time=0);
};

#endif //ANIMATION_HPP
