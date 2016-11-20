#include "title.hpp"
#include <SDL.h>

void Title::create(Global& g) {
    global = &g;
    Shader* shader = global->resources.get<Shader>("shader");

    StyleSheet* styles = global->resources.get<StyleSheet>("style");
    const Style& titleStyle = styles->get("title");

    title.reset(new TextNode("title",
                global->resources.get<Font>(titleStyle.getFont()),
                "Snake",
                titleStyle.getFontSize(),
                shader));
    title->setTint(titleStyle.getColor());

    const Style& menuButtonStyle = styles->get("menuButton");

    hello.reset(new TextNode("hello",
                global->resources.get<Font>(menuButtonStyle.getFont()),
                "Hello",
                menuButtonStyle.getFontSize(),
                shader));
    hello->setTint(menuButtonStyle.getColor());
    hello->setTransform(translate(Vec3f{ 10.0f, 100.0f, 0.0f }));

    scene.reset(new DrawableNode("scene"));
    scene->addChild(title.get());
    scene->addChild(hello.get());
}

void Title::shutdown() {
}

SnakeState* Title::update() {
    return SnakeState::update();
}

void Title::draw() {
    Mat4f projection = orthographic(0.0f, 0.0f, (float)global->resolution.x, (float)global->resolution.y);
    scene->draw(projection);
}
