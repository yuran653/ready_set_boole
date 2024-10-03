#include "BitwiseAdd.hpp"

uint32_t BitwiseAdd::bitwise_add(const uint32_t a, const uint32_t b) {
    uint32_t sum = a;
    uint32_t carry = b;
    while (carry != 0) {
        uint32_t new_sum = sum ^ carry; // Sum without carry
        carry = (sum & carry) << 1;     // Carry calculation
        sum = new_sum;
    }
    return sum;
}
