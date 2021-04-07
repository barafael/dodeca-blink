#pragma once

#include "does_things.hpp"

class DodecaState: public ThingDoer {
public:
    explicit DodecaState(String name) : name(name) {}

    virtual void advance() = 0;

    String *get_name() {
        return &name;
    }

    virtual ~DodecaState() = default;

private:
    String name;
};
