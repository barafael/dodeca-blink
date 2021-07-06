#pragma once

#include "FastLED.h"

#include "volterra.hpp"

class Entity {
    public:
    Entity(position head, position tail, CRGB color) : head(head), tail(tail), color(color) {
    }

    private:
    position head;
    position tail;

    CRGB color;
};