#include <cassert>
#include <iostream>
#include <random>
#include "BitwiseMult.hpp"

int main() {
    std::random_device rd;                                // Seed for random number engine
    std::mt19937 gen(rd());                               // Mersenne Twister engine seeded with random_device
    std::uniform_int_distribution<> dist(0, 10000);    // Uniform distribution between 0 and 10000

    for (uint32_t i = 0; i < 10000; i++) {
        // Generate two random integers 'a' and 'b'
        uint32_t a = dist(gen);
        uint32_t b = dist(gen);
        assert(BitwiseMult::bitwise_mult(a, b) == a * b);
    }

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
