#pragma once

#include <stdint.h>

struct Vector2U {
public:
    Vector2U(uint32_t x = 0, uint32_t y = 0);
    uint32_t x, y;
};