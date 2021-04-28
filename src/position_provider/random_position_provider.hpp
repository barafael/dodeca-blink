#pragma once

#include "producer.hpp"
#include "position_provider.hpp"

#include <FastLED.h>

class RandomPositionProvider : public PositionProvider {
public:
    DodecaPosition read() override {
        return DodecaPosition(random8(30), random8(100)); // TODO inclusive or exclusive bounds? Not documented.
    }
};