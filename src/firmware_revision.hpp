#pragma once

#include <cstdint>

typedef union revision_u {
    struct {
        uint32_t major: 8;
        uint32_t minor: 8;
        uint32_t patch: 16;
    };
    uint32_t revision;
} revision_t;

constexpr revision_t REVISION {
    {
        0,
        1,
        8,
    },
};