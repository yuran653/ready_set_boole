#include "BitwiseMult.hpp"
#include "BitwiseAdd.hpp"

int BitwiseMult::bitwiseMult(int a, int b) {
    if (a < 0 || b < 0) {
        throw BitwiseMult::InputError("Inputs must be natural numbers: ["
            + std::to_string(a) + "],[" + std::to_string(b) + "]");
    }
    int result = 0;
    while (b > 0) {
        if ((b & 1) == 1)                               // Check if the least significant bit of 'b' is 1
            result = BitwiseAdd::bitwiseAdd(result, a); // Add 'a' to 'result'
        a = a << 1;                                     // Multiply 'a' by 2 using left shift
        b = b >> 1;                                     // Divide 'b' by 2 using right shift

    }
    return result;
}
