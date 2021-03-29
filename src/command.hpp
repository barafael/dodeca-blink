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
};

bool is_command(int val) {
    return val == 'i' || val == 'd' || val == 'a' || val == 'b' || val == 'c' || val == 'n' || val == 'p';
}

enum class LampState : uint32_t
{
    FADE_PALETTE_STATE  = 'P',
    TEST_PATTERN_STATE  = 'T',
    COLOR_SPARKLE_STATE = 'S',
    RANDOM_BLINK_STATE  = 'R',
    BLUE_BLINK_STATE    = 'B',
    WHITE_BLINK_STATE   = 'W',
};

bool is_state(int val) {
    return val == 'P' || val == 'T' || val == 'S' || val == 'R' || val == 'B' || val == 'W';
}

const LampState state_sequence[] = {
    LampState::FADE_PALETTE_STATE, LampState::TEST_PATTERN_STATE, LampState::COLOR_SPARKLE_STATE,
    LampState::RANDOM_BLINK_STATE, LampState::BLUE_BLINK_STATE,   LampState::WHITE_BLINK_STATE,
};

LampState next_state(LampState current) {
    switch (current) {
        case LampState::FADE_PALETTE_STATE:
            return LampState::TEST_PATTERN_STATE;
            break;
        case LampState::TEST_PATTERN_STATE:
            return LampState::COLOR_SPARKLE_STATE;
            break;
        case LampState::COLOR_SPARKLE_STATE:
            return LampState::RANDOM_BLINK_STATE;
            break;
        case LampState::RANDOM_BLINK_STATE:
            return LampState::BLUE_BLINK_STATE;
            break;
        case LampState::BLUE_BLINK_STATE:
            return LampState::WHITE_BLINK_STATE;
            break;
        case LampState::WHITE_BLINK_STATE:
            return LampState::FADE_PALETTE_STATE;
            break;
    }
}

LampState previous_state(LampState current) {
    switch (current) {
        case LampState::FADE_PALETTE_STATE:
            return LampState::WHITE_BLINK_STATE;
            break;
        case LampState::TEST_PATTERN_STATE:
            return LampState::FADE_PALETTE_STATE;
            break;
        case LampState::COLOR_SPARKLE_STATE:
            return LampState::TEST_PATTERN_STATE;
            break;
        case LampState::RANDOM_BLINK_STATE:
            return LampState::COLOR_SPARKLE_STATE;
            break;
        case LampState::BLUE_BLINK_STATE:
            return LampState::RANDOM_BLINK_STATE;
            break;
        case LampState::WHITE_BLINK_STATE:
            return LampState::BLUE_BLINK_STATE;
            break;
    }
}
