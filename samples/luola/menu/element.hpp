#pragma once
#include "../global.hpp"

class Element {
    bool isMouseInside;

public:
    Element() : isMouseInside(false) { }
    virtual ~Element() { }

    virtual Vec2f getPosition() const { return{ 0, 0 }; }
    virtual Vec2f getSize() const { return{ 0, 0 }; }
    virtual void draw(const Mat4f& projection, const Mat4f& transform = Mat4f()) { }

    void mouseMove(Vec2f mouse) {
        bool inside = isInside(mouse);
        if (inside && !isMouseInside) {
            onEnter();
        }
        if (!inside && isMouseInside) {
            onLeave();
        }
        isMouseInside = inside;
    }

    void mouseDown() {
        onPress(isMouseInside);
    }

    void mouseUp() {
        onRelease(isMouseInside);
    }

    bool isInside(Vec2f position) {
        const Vec2f& p = getPosition();
        const Vec2f& s = getSize();
        return position.x > p.x && position.x < p.x + s.x &&
               position.y > p.y && position.y < p.y + s.y;
    }

protected:
    virtual void onEnter() { }
    virtual void onLeave() { }
    virtual void onPress(bool inside) { }
    virtual void onRelease(bool inside) { }

};
