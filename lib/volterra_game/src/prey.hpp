#pragma once

#include "entity.hpp"

#include "FastLED.h"

#include "volterra.hpp"

class Prey : public Entity {
    public:
    Prey(position head, position tail) : Entity(head, tail, CRGB::DarkGreen) {};
};
