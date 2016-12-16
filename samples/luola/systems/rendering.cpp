#include "rendering.hpp"
#include "../components/position.hpp"
#include "../components/drawable.hpp"

void RenderingSystem::render(EntityCollection& entities, const Mat4f& projection) {
    entities.map((std::function<void(PositionComponent*, DrawableComponent*)>)[&] (PositionComponent* p, DrawableComponent* d) {
        d->shader->apply();
        d->shader->setUniform("transform", projection * translate(p->position.x, p->position.y, 0.0f) * rotate(p->rotation, Vec3f{ 0, 0, 1 }));
        d->shape.draw();
    });
}
