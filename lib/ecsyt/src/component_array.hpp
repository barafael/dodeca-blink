#pragma once

#include <unordered_map>

#include "packed_array.hpp"
template <typename T> class ComponentArray : public PackedArray {
    public:
    T &get_data_of_entity(Entity entity) {
        return this->components[this->entity_to_index[entity]];
    }

    void insert_data(Entity entity, T component) {
        size_t new_index = this->size;

        this->entity_to_index[entity]    = new_index;
        this->index_to_entity[new_index] = entity;

        this->components[new_index] = component;

        this->size += 1;
    }

    void remove_data(Entity entity) {
        size_t index_of_removed = this->entity_to_index[entity];
        size_t index_of_last    = this->size - 1;

        this->components[index_of_removed] = this->components[index_of_last];

        Entity entity_of_last_element                 = this->index_to_entity[index_of_last];
        this->entity_to_index[entity_of_last_element] = index_of_removed;
        this->index_to_entity[index_of_removed]       = entity_of_last_element;

        this->entity_to_index.erase(entity);
        this->index_to_entity.erase(index_of_last);

        this->size -= 1;
    }

    void entity_destroyed(Entity entity) override {
        if (this->entity_to_index.find(entity) != this->entity_to_index.end()) {
            this->remove_data(entity);
        }
    }

    private:
    std::array<T, MAX_ENTITIES> components = {};

    std::unordered_map<Entity, size_t> entity_to_index = {};
    std::unordered_map<size_t, Entity> index_to_entity = {};

    size_t size { 0 };
};
