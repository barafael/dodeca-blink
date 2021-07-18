#pragma once

#include <cstdint>

enum class Command : uint8_t {
    NONE = 0,

    NEXT_STATE     = 'n',
    PREVIOUS_STATE = 'p',

    INCREASE_BRIGHTNESS = 'i',
    DECREASE_BRIGHTNESS = 'd',

    ACTION_A = 'a',
    ACTION_B = 'b',
    ACTION_C = 'c',

    GET_COMMAND_NAMES = 'g',

    GET_STATE_LIST = 'l',

    GET_FIRMWARE_REVISION = 'v',

    BLOB = 'o',
};

bool is_command(uint8_t val) {
    return val == 'i' || val == 'd' || val == 'a' || val == 'b' || val == 'c' || val == 'n' || val == 'p' ||
           val == 'l' || val == 'v' || val == 'g' || val == 'o';
}