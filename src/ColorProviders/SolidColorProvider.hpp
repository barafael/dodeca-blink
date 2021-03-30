#pragma once

#include "Producer.hpp"

#include <FastLED.h>

class SolidColorProvider: public Producer<CHSV> {
  public:
    explicit SolidColorProvider(CHSV color): color(color) {
    }

    void setColor(CHSV color) {
        this->color = color;
    }

    CHSV read() override {
        return color;
    }

  private:
    CHSV color;
};