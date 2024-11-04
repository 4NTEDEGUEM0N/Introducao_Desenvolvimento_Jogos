#ifndef ANIMATION_HPP
#define ANIMATION_HPP

using namespace std;

class Animation {
    int frameStart;
    int frameEnd;
    float frameTime;

    Animation(int frame_start, int frame_end, float frame_time);
};

#endif //ANIMATION_HPP
