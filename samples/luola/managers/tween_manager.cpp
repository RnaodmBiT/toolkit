#include "tween_manager.hpp"

TweenManager::TweenManager(Global& global) : global(global) { }

void TweenManager::create(float duration,
                          Easing::Function easing,
                          TweenFunction function,
                          float delay) {
    float now = global.time();
    tweens.push_back({ now + delay,
                       now + delay + duration,
                       easing,
                       function });
}

void TweenManager::update() {
    float now = global.time();
    for (Tween& tween : tweens) {
        float x = (now - tween.start) / (tween.end - tween.start);
        if (x >= 0.0f && x <= 1.0f) {
            tween.callback(tween.interpolation(x));
        }
    }

    auto end = std::remove_if(tweens.begin(), tweens.end(), [&] (Tween& tween) {
        bool remove = tween.end <= now;
        if (remove) {
            tween.callback(1.0f); // finish off the tween
        }
        return remove;
    });

    tweens.erase(end, tweens.end());
}
