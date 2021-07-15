#pragma once

#include <memory>
#include <unordered_map>

#include "component.hpp"
#include "component_array.hpp"
#include "packed_array.hpp"

class ComponentManager {
    public:
    template <typename T> void register_component() {
        const char *type_name = typeid(T).name();

        this->component_types.insert({ type_name, next_component_type });

        this->component_arrays.insert({ type_name, std::make_shared<ComponentArray<T>>() });

        this->next_component_type += 1;
    }

    template <typename T> ComponentType get_component_type() {
        const char *type_name = typeid(T).name();

        return this->component_types[type_name];
    }

    template <typename T> void add_component(Entity entity, T component) {
        this->get_component_array<T>()->insert_data(entity, component);
    }

    template <typename T> void remove_component(Entity entity) {
        get_component_array<T>()->remove_data(entity);
    }

    template <typename T> T &get_component(Entity entity) {
        return get_component_array<T>()->get_data(entity);
    }

    void entity_destroyed(Entity entity) {
        // Notify each component array that an entity has been destroyed
        // If it has a component for that entity, it will remove it
        for (auto const &pair : this->component_arrays) {
            auto const &component = pair.second;

            component->entity_destroyed(entity);
        }
    }

    private:
    std::unordered_map<const char *, ComponentType> component_types {};

    std::unordered_map<const char *, std::shared_ptr<PackedArray>> component_arrays;

    ComponentType next_component_type {};

    template <typename T> std::shared_ptr<ComponentArray<T>> get_component_array() {
        const char *type_name = typeid(T).name();

        return std::static_pointer_cast<ComponentArray<T>>(this->component_arrays[type_name]);
    }
};
