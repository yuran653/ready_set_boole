#include "GrayCode.hpp"

uint32_t GrayCode::gray_code(const uint32_t n) {
    return n ^ (n >> 1);
}

// Step 1 (in parentheses):
// Perform a bitwise right shift on n by 1 position. This effectively divides n by 2,
// aligning each bit with the next higher-order bit of the original value
//
// Step 2:
// Perform a bitwise XOR between n and its right-shifted value
// This ensures that only the bits where the original and shifted values differ are set to 1
// The result is the Gray code representation of n