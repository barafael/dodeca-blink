#pragma once

#include <cstddef>

#ifdef BOARD_VARIANT_A

#define LED_TYPE SK6812

constexpr size_t LEDS_PER_STRIP = 60;
constexpr size_t STRIP_COUNT    = 6;

constexpr size_t LEDS_PER_EDGE = 10;

constexpr size_t INITIAL_BRIGHTNESS = 25;
constexpr size_t BRIGHTNESS_STEP = 10;

constexpr size_t FADE_INTERVAL_MS = 20;
constexpr size_t FADE_STEP = 1;

#elif defined(BOARD_VARIANT_B)

#define LED_TYPE WS2811

constexpr size_t LEDS_PER_STRIP = 60;
constexpr size_t STRIP_COUNT    = 6;

constexpr size_t LEDS_PER_EDGE = 10;

constexpr size_t INITIAL_BRIGHTNESS = 25;
constexpr size_t BRIGHTNESS_STEP = 10;

constexpr size_t FADE_INTERVAL_MS = 20;
constexpr size_t FADE_STEP = 1;


#endif
