#pragma once

#include <cstddef>
#include <cstdint>

enum class Command : uint32_t
{
    NONE = 0,

    NEXT_STATE     = 'n',
    PREVIOUS_STATE = 'p',

    INCREASE_BRIGHTNESS = 'i',
    DECREASE_BRIGHTNESS = 'd',

    ACTION_A = 'a',
    ACTION_B = 'b',
    ACTION_C = 'c',

    GET_STATE_LIST = 'L',
};

bool is_command(int val) {
    return val == 'i' || val == 'd' || val == 'a' || val == 'b' || val == 'c' || val == 'n' || val == 'p' || val == 'L';
}