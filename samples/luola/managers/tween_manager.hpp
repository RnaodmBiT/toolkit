#pragma once
#include <functional>
#include "easing.hpp"
#include "../global.hpp"

typedef std::function<void(float)> TweenFunction;

struct Tween {
    float start, end;
    Easing::Function interpolation;
    TweenFunction callback;
};

class TweenManager {
    Global& global;
    std::vector<Tween> tweens;

public:
    TweenManager(Global& global);

    void create(float duration, Easing::Function easing, TweenFunction function, float delay = 0);

    void update();
};
