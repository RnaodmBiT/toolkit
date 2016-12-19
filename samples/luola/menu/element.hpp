#pragma once
#include "../global.hpp"

class Element {
public:
    virtual ~Element() { }

    virtual Vec2f getPosition() const { return{ 0, 0 }; }
    virtual Vec2f getSize() const { return{ 0, 0 }; }
    virtual void draw(const Mat4f& projection) { }

    virtual void mouseMove(Vec2f mouse) { }
    virtual void mouseDown(Vec2f mouse) { }
    virtual void mouseUp(Vec2f mouse) { }

    bool isInside(Vec2f position) {
        const Vec2f& p = getPosition();
        const Vec2f& s = getSize();
        return position.x > p.x && position.x < p.x + s.x &&
               position.y > p.y && position.y < p.y + s.y;
    }
};
