#pragma once
#include "../includes.hpp"

class Element {
    bool isMouseInside;

protected:
    float alpha;

public:
    Element() : isMouseInside(false), alpha(1) { }
    virtual ~Element() { }

    virtual Vec2f getPosition() const { return{ 0, 0 }; }
    virtual Vec2f getSize() const { return{ 0, 0 }; }
    virtual void draw(const Mat4f& projection, const Mat4f& transform = Mat4f(), float alpha = 1) { }

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

    void setAlpha(float a) {
        alpha = a;
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
