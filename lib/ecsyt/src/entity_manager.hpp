#pragma once

#include "queue.hpp"

#include "entity.hpp"
#include "signature.hpp"

#include <array>

class EntityManager {
    public:
    EntityManager() {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) { this->entity_pool.push(entity); }
    }

    Entity create_entity() {
        return this->entity_pool.pop();
    }

    void destroy_entity(Entity e) {
        this->signatures[e].reset();
        this->entity_pool.push(e);
    }

    size_t alive_count() {
        return MAX_ENTITIES - this->entity_pool.len();
    }

    void set_signature(Entity entity, Signature signature) {
        this->signatures[entity] = signature;
    }

    Signature get_signature(Entity entity) {
        return this->signatures[entity];
    }

    private:
    std::array<Signature, MAX_ENTITIES> signatures {};

    Queue<Entity, MAX_ENTITIES> entity_pool {};
};
