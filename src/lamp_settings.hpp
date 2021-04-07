#pragma once

#include <Preferences.h>
#include <cstddef>
#include <cstdint>
#include <constants.hpp>

class LampSettings {
public:
    explicit LampSettings(Preferences &persistent_state) : persistent_state(persistent_state) {
    }

    uint8_t get_brightness() const {
        return brightness;
    }

    size_t get_index() const {
        return index;
    }

    void set_brightness(uint8_t brightness) {
        this->brightness = brightness;
    }

    void set_index(size_t index) {
        this->index = index;
    }

    void serialize() {
        persistent_state.putUInt("state-index", index);
        persistent_state.putUChar("brightness", brightness);
    }

private:

    size_t index = 0;
    uint8_t brightness = INITIAL_BRIGHTNESS;

    Preferences &persistent_state;
};