#pragma once

#include "producer.hpp"
#include "states/does_things.hpp"

#include <FastLED.h>

// TODO rename all providers to producers
class ColorProvider: public Producer<CHSV>, public ThingDoer {

};