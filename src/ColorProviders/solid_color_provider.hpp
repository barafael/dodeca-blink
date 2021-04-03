#pragma once

#include "producer.hpp"

#include <FastLED.h>

class SolidColorProvider : public Producer<CHSV> {
public:
    explicit SolidColorProvider(CHSV color) : color(color) {
    }

    void set_color(CHSV color) {
        this->color = color;
    }

    CHSV get_color() {
        return color;
    }

    CHSV read() override {
        return color;
    }

private:
    CHSV color;
};