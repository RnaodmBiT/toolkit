#pragma once
#include <cmath>
#include <maths.hpp>

using namespace tk::core;

namespace Easing {

    typedef float(*Function)(float);

    static float linear(float p) {
        return p;
    }

    static float quadraticIn(float p) {
        return p * p;
    }

    static float quadraticOut(float p) {
        return -(p * (p - 2));
    }

    static float quadraticInOut(float p) {
        if (p < 0.5) {
            return 2 * p * p;
        } else {
            return (-2 * p * p) + (4 * p) - 1;
        }
    }

    static float cubicIn(float p) {
        return p * p * p;
    }

    static float cubicOut(float p) {
        float f = (p - 1);
        return f * f * f + 1;
    }

    static float cubicInOut(float p) {
        if (p < 0.5) {
            return 4 * p * p * p;
        } else {
            float f = ((2 * p) - 2);
            return 0.5f * f * f * f + 1;
        }
    }

    static float quarticIn(float p) {
        return p * p * p * p;
    }

    static float quarticOut(float p) {
        float f = (p - 1);
        return f * f * f * (1 - p) + 1;
    }

    static float quarticInOut(float p) {
        if (p < 0.5) {
            return 8 * p * p * p * p;
        } else {
            float f = (p - 1);
            return -8 * f * f * f * f + 1;
        }
    }

    static float quinticIn(float p) {
        return p * p * p * p * p;
    }

    static float quinticOut(float p) {
        float f = (p - 1);
        return f * f * f * f * f + 1;
    }

    static float quinticInOut(float p) {
        if (p < 0.5) {
            return 16 * p * p * p * p * p;
        } else {
            float f = ((2 * p) - 2);
            return  0.5f * f * f * f * f * f + 1;
        }
    }

    static float sineIn(float p) {
        return std::sin((p - 1) * pi / 2) + 1;
    }

    static float sineOut(float p) {
        return std::sin(p * pi / 2);
    }

    static float sineInOut(float p) {
        return 0.5f * (1 - std::cos(p * pi));
    }

    static float circularIn(float p) {
        return 1 - std::sqrt(1 - (p * p));
    }

    static float circularOut(float p) {
        return sqrt((2 - p) * p);
    }

    static float circularInOut(float p) {
        if (p < 0.5) {
            return 0.5f * (1 - std::sqrt(1 - 4 * (p * p)));
        } else {
            return 0.5f * (std::sqrt(-((2 * p) - 3) * ((2 * p) - 1)) + 1);
        }
    }

    static float exponentialIn(float p) {
        return (p == 0.0) ? p : std::pow(2.0f, 10 * (p - 1));
    }

    static float exponentialOut(float p) {
        return (p == 1.0) ? p : 1 - std::pow(2.0f, -10 * p);
    }

    static float exponentialInOut(float p) {
        if (p == 0.0 || p == 1.0) return p;

        if (p < 0.5) {
            return 0.5f * std::pow(2.0f, (20 * p) - 10);
        } else {
            return -0.5f * std::pow(2.0f, (-20 * p) + 10) + 1;
        }
    }

    static float elasticIn(float p) {
        return std::sin(13 * pi / 2 * p) * std::pow(2.0f, 10 * (p - 1));
    }

    static float elasticOut(float p) {
        return std::sin(-13 * pi / 2 * (p + 1)) * std::pow(2.0f, -10 * p) + 1;
    }

    static float elasticInOut(float p) {
        if (p < 0.5) {
            return 0.5f * std::sin(13 * pi / 2 * (2 * p)) * std::pow(2.0f, 10 * ((2 * p) - 1));
        } else {
            return 0.5f * (std::sin(-13 * pi / 2 * ((2 * p - 1) + 1)) * std::pow(2.0f, -10 * (2 * p - 1)) + 2);
        }
    }

    static float backIn(float p) {
        return p * p * p - p * std::sin(p * pi);
    }

    static float backOut(float p) {
        float f = (1 - p);
        return 1 - (f * f * f - f * std::sin(f * pi));
    }

    static float backInOut(float p) {
        if (p < 0.5) {
            float f = 2 * p;
            return 0.5f * (f * f * f - f * std::sin(f * pi));
        } else {
            float f = (1 - (2 * p - 1));
            return 0.5f * (1 - (f * f * f - f * std::sin(f * pi))) + 0.5f;
        }
    }

    static float bounceOut(float p) {
        if (p < 4 / 11.0) {
            return (121 * p * p) / 16.0f;
        } else if (p < 8 / 11.0) {
            return (363 / 40.0f * p * p) - (99 / 10.0f * p) + 17 / 5.0f;
        } else if (p < 9 / 10.0) {
            return (4356 / 361.0f * p * p) - (35442 / 1805.0f * p) + 16061 / 1805.0f;
        } else {
            return (54 / 5.0f * p * p) - (513 / 25.0f * p) + 268 / 25.0f;
        }
    }

    static float bounceIn(float p) {
        return 1 - bounceOut(1 - p);
    }

    static float bounceInOut(float p) {
        if (p < 0.5) {
            return 0.5f * bounceIn(p * 2);
        } else {
            return 0.5f * bounceOut(p * 2 - 1) + 0.5f;
        }
    }
}
