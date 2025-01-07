#include "BitwiseMult.hpp"

uint32_t BitwiseMult::bitwise_add(const uint32_t a, const uint32_t b) {
    uint32_t sum = a;
    uint32_t carry = b;
    while (carry != 0) {
        uint32_t new_sum = sum ^ carry; // Sum without carry
        carry = (sum & carry) << 1;     // Carry calculation
        sum = new_sum;
    }
    return sum;
}

uint32_t BitwiseMult::bitwise_mult(const uint32_t a, const uint32_t b) {
    uint32_t result = 0;
    uint32_t mult_a = a;
    uint32_t mult_b = b;
    while (mult_b > 0) {
        if ((mult_b & 1) == 1)                                  // Check if the least significant bit of 'b' is 1
            result = BitwiseMult::bitwise_add(result, mult_a);  // Add 'a' to 'result'
        mult_a = mult_a << 1;                                   // Multiply 'a' by 2 using left shift
        mult_b = mult_b >> 1;                                   // Divide 'b' by 2 using right shift

    }
    return result;
}
