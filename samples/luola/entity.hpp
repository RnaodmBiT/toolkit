#pragma once
#include <vector>
#include <memory>
#include <map>
#include <core.hpp>
#include "components/component.hpp"

using namespace tk::core;

class Entity {
    std::vector<ComponentPtr> components;

public:

    template <class T, class ...Args>
    void add(Args&& ...args) {
        components.emplace_back(new T(std::forward<Args>(args)...));
    }

    template <class T>
    T* get() const {
        for (const auto& ptr : components) {
            T* cast = dynamic_cast<T*>(ptr.get());
            if (cast) {
                return cast;
            }
        }
        return nullptr;
    }

    template <class T>
    bool has() const {
        return get<T>() != nullptr;
    }

    template <class T, class U, class ...Types>
    bool has() const {
        return has<T>() && has<U, Types...>();
    }
};


class EntityCollection {
    std::vector<Entity> entities;
public:

    Entity& create() {
        entities.emplace_back();
        return entities[entities.size() - 1];
    }

    template <class ...Types>
    std::vector<Entity*> filter() {
        std::vector<Entity*> list;
        for (auto& e : entities) {
            if (e.has<Types...>()) {
                list.push_back(&e);
            }
        }
        return list;
    }

    template <class ...Types>
    void map(std::function<void(Types*...)> func) {
        for (auto& e : entities) {
            if (e.has<Types...>()) {
                func(e.get<Types>()...);
            }
        }
    }
};