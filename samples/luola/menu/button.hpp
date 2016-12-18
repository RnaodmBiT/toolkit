#include "../global.hpp"
#include "../text.hpp"

class Button {
    enum State { Up, Over, Down, DownAndOut } state;

    Text label;

    bool isInside(Vec2f position) {
        const Vec2f& p = label.getPosition();
        const Vec2f& s = label.getSize();

        if (position.x > p.x && position.x < p.x + s.x && position.y > p.y && position.y < p.y + s.y) {
            return true;
        }
        return false;
    }
    friend class Menu;
public:
    std::function<void()> onClick;

    Button() : state(Up) { }
};
