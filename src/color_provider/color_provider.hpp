#pragma once

#include "producer.hpp"
#include "states/does_things.hpp"

#include <FastLED.h>

class ColorProvider: public Producer<CHSV>, public ThingDoer {

};