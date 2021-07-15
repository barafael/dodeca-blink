#pragma once

#include "entity.hpp"

class PackedArray {
    public:
    virtual ~PackedArray() = default;

    virtual void entity_destroyed(Entity entity) = 0;
};
