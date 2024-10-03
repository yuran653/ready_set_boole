#include "GrayCode.hpp"

uint32_t GrayCode::gray_code(const uint32_t n) {
    return n ^ (n >> 1);
}
