#pragma once

#include <cstdint>
#include <cstddef>

#include "command.hpp"

class ThingDoer {
    public:

    virtual bool do_thing(Command id) {
        return false;
    }

    virtual bool do_thing(Command id, uint8_t *args, size_t count) {
        return false;
    }

    virtual char const *const get_thing_name(Command id) {
        return "";
    }

    virtual ~ThingDoer() = default;
};