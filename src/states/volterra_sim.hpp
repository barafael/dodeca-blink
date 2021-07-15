#pragma once

#include <FastLED.h>

#include <cstddef>

#include "command.hpp"
#include "constants.hpp"
#include "dodeca_state.hpp"
#include "led_data.hpp"

#include "volterra.hpp"

class VolterraSim : public DodecaState {
    public:
    VolterraSim(String name) : DodecaState(name) {
    }

    bool do_thing(Command id) override {
        switch (id) {
            case Command::ACTION_A: run = !run; return true;

            default: return false;
        }
    }

    char const *const get_thing_name(Command id) override {
        switch (id) {
            case Command::ACTION_A: return "Pause/Play";
            default: return "";
        }
    }

    void advance() override {
    }

    private:
    bool run = true;
};
