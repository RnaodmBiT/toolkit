#pragma once
#include "global.hpp"

namespace Shapes {
    inline Shape createShipShape(const Vec4f& color) {
        Vec2f points[] = {
            { 10, 0 },
            { -5, 7.5f },
            { -2.5f, 0 },

            { 10, 0 },
            { -2.5f, 0 },
            { -5, -7.5f }
        };

        Vec4f colors[] = {
            color, color, color,
            color, color, color
        };

        Vec2f uvs[] = {
            { 0, 0 },{ 0, 0 },{ 0, 0 },
            { 0, 0 },{ 0, 0 },{ 0, 0 },
        };

        return Shape::polygon(points, colors, uvs, 6);
    }

    inline Shape createBulletShape(const Vec4f& color) {
        Vec2f points[] = {
            {5, 0},
            {0, 2},
            {0, -2}
        };
        Vec4f colors[] = {
            color,color,color
        };

        Vec2f uvs[] = {
            {0,0},{0,0},{0,0}
        };
        return Shape::polygon(points, colors, uvs, 3);
    }
}
