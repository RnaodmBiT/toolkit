#pragma once
#include "entity.hpp"
#include "shapes.hpp"
#include "components/position.hpp"
#include "components/drawable.hpp"
#include "components/physics.hpp"
#include "components/ship_control.hpp"

inline void addGameTypes(EntityFactory& factory, Global& global, bool server) {
    factory.addType("ship", EntityFactory::Builder([=, &global] (EntityCollection& collection, Blob::const_iterator& blob) {
        int id;
        Vec2f position;
        Vec4f color;
        deserialize(blob, id, position, color);

        Entity& e = collection.create(id);
        e.add<PositionComponent>(position, -pi / 2);
        e.add<PhysicsComponent>();
        e.add<ShipControl>();

        if (!server) {
            e.add<DrawableComponent>(createShipShape(color),
                                     global.cache.get<Shader>("shader"),
                                     nullptr);
        }

        return id;
    }));
}