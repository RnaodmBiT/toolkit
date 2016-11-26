#include "title.hpp"
#include <SDL.h>

DrawableNode* Title::createMenuNode(const std::string& name, const json& data) {
    StyleSheet* sheet = global->resources.get<StyleSheet>("style");
    const Style& style = sheet->get(data["style"]);
    DrawableNode* node = uiFactory.build(name, data, style, global->resources);

    Mat4f transform = translate((float)style.getPadding().x, (float)style.getPadding().y, 0.0f);

    if (data.count("children")) {
        const json& children = data["children"];
        for (auto it = children.begin(); it != children.end(); ++it) {
            DrawableNode* child = createMenuNode(it.key(), it.value());
            child->setTransform(transform);

            Vec2f size = child->getSize();
            transform = transform * translate(0.0f, size.y, 0.0f);

            node->addChild(child);
        }
    }

    menu.emplace_back(node);
    return node;
}

void Title::create(Global& g) {
    global = &g;
    uiFactory.addDefaultTypes();

    scene.reset(new DrawableNode("scene"));
    scene->setShader(global->resources.get<Shader>("shader"));
    json menu = json::parse(readFile("data/styles/snake_menu.json").c_str());

    for (auto it = menu.begin(); it != menu.end(); ++it) {
        scene->addChild(createMenuNode(it.key(), it.value()));
    }
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
