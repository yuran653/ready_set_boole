#include "Curve.hpp"

double Curve::map(uint16_t x, uint16_t y) {
    uint32_t result = 0;
    for (int i = 0; i < 16; ++i) {
        uint32_t bit_x = (x >> i) & 1U;
        uint32_t bit_y = (y >> i) & 1U;
        result |= bit_x << (2 * i);
        result |= bit_y << (2 * i + 1);
    }
    double max_value = (1ULL << 32) - 1;
    return static_cast<double>(result) / max_value;
}

std::pair<uint16_t, uint16_t> Curve::inverse_map(double z) {
    uint32_t result = static_cast<uint32_t>(z * ((1ULL << 32) - 1));
    uint16_t x = 0;
    uint16_t y = 0;
    for (int i = 0; i < 16; ++i) {
        uint16_t bit_x = (result >> (2 * i)) & 1U;
        uint16_t bit_y = (result >> (2 * i + 1)) & 1U;
        x |= (bit_x << i);
        y |= (bit_y << i);
    }
    return {x, y};
}
