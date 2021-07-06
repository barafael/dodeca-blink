#pragma once

#include "entity.hpp"

#include "FastLED.h"

#include "volterra.hpp"

#include <cstddef>

constexpr size_t INITIAL_PREDATOR_ENERGY = 10;

class Predator : public Entity {
    public:
    Predator(position head, position tail) : Entity(head, tail, CRGB::DarkRed) {};

    private:
    size_t energy = INITIAL_PREDATOR_ENERGY;
};
