#pragma once

#include "producer.hpp"
#include "color_provider.hpp"

#include <FastLED.h>

class SolidColorProvider : public ColorProvider {
public:
    explicit SolidColorProvider(CHSV color) : color(color) {
    }

    CHSV read() override {
        return color;
    }

private:
    CHSV color;
};