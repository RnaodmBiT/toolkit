#include "background.hpp"

Background::Background(Global& global) : global(global) {
    shader = global.cache.get<Shader>("scrolling");
    shape = Shape::rectangle({ 0, 0 }, { (float)global.width, (float)global.height });

    layers.push_back(global.cache.get<Texture>("background0"));
    scales.push_back({ 4, 1.3f });

    layers.push_back(global.cache.get<Texture>("background1"));
    scales.push_back({ 2, 1.2f });

    layers.push_back(global.cache.get<Texture>("background2"));
    scales.push_back({ 1, 1 });

    for (Texture* layer : layers) {
        layer->setWrapMode(Texture::Wrap, Texture::Clamp);
        layer->enableMipmap(false);
    }
}

void Background::draw(const Mat4f& projection, const Vec2f& camera) {
    shader->apply();
    shader->setUniform("transform", projection);

    Vec2f position = camera / Vec2f{ (float)global.width, (float)global.height };

    for (int i = 0; i < layers.size(); ++i) {
        float height = (float)layers[i]->getSize().y;
        float offset = ((float)global.height - height) / (float)global.height - 0.5f;
        float scale = (float)(global.height) / height;

        Vec2f pos;
        pos.x = position.x / scales[i].x;
        pos.y = position.y / scales[i].y - offset;

        shader->setUniform("image", *layers[i]);
        shader->setUniform("offset", pos);
        shader->setUniform("scale", Vec2f{ 1, scale });
        shape.draw();
    }
}
