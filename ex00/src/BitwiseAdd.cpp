#include "BitwiseAdd.hpp"

int BitwiseAdd::bitwiseAdd(int a, int b) {
    if (a < 0 || b < 0) {
        throw BitwiseAdd::InputError("Inputs must be natural numbers.");
    }
    while (b != 0) {
        int sum = a ^ b;            // Sum without carry
        int carry = (a & b) << 1;   // Carry calculation
        a = sum;
        b = carry;
    }
    return a;
}
