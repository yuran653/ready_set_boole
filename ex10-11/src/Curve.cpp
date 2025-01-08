#include "Curve.hpp"

// Maps a pair of 16-bit integers (x, y) to a normalized double value in the range [0, 1]
double Curve::map(uint16_t x, uint16_t y) {
    // Initialize a 32-bit integer to store the interleaved bits of x and y
    uint32_t result = 0;
    // Interleave the bits of x and y
    for (int i = 0; i < 16; ++i) {
        // 1U - representation of 1 with the 'unsigned int' type
        // (var >> i): Right shift x by i positions to bring the i-th bit
        // to the least significant bit (LSB) position
        // & 1U: Perform a bitwise AND with 1U to isolate the LSB, which is the i-th bit of var
        uint32_t bit_x = (x >> i) & 1U; // Extract the i-th bit of x
        uint32_t bit_y = (y >> i) & 1U; // Extract the i-th bit of y
        // Place the extracted bit in the (2*i) - refers to even positions
        // or (2*i+1)- refers to odd positions 'position' of result
        // << 'position': left shift bit by position's value
        // to set it in the correct interleaved position
        result |= bit_x << (2 * i); // Place bit_x in the 2*i position of result
        result |= bit_y << (2 * i + 1); // Place bit_y in the 2*i + 1 position of result
    }
    // Normalize the result to the range [0, 1] by dividing by max_value
    return static_cast<double>(result) / UINT32_MAX;
}

// Decodes a normalized double value back into a pair of 16-bit integers
std::pair<uint16_t, uint16_t> Curve::inverse_map(double z) {
    // Convert the normalized double value back into a 32-bit integer
    uint32_t result = static_cast<uint32_t>(z * UINT32_MAX);
    // Initialize x and y to store the extracted bits
    uint16_t x = 0;
    uint16_t y = 0;
    // De-interleave the bits from the 32-bit result into x and y
    for (int i = 0; i < 16; ++i) {
        // Extract the bit at 2*i position for x
        uint16_t bit_x = (result >> (2 * i)) & 1U;
        // Extract the bit at 2*i + 1 position for y
        uint16_t bit_y = (result >> (2 * i + 1)) & 1U;
        // Place the extracted bit_x in the i-th position of x
        x |= (bit_x << i);
        // Place the extracted bit_y in the i-th position of y
        y |= (bit_y << i);
    }
    return {x, y};
}
