#include "BitwiseAdd.hpp"
#include <random>

int main() {
    std::random_device rd;                                // Seed for random number engine
    std::mt19937 gen(rd());                               // Mersenne Twister engine seeded with random_device
    std::uniform_int_distribution<> dist(-100, 10000);    // Uniform distribution between 0 and 10000

    for (int i = 0; i < 10000; i++) {
        // Generate two random integers 'a' and 'b'
        int a = dist(gen);
        int b = dist(gen);
        int result = 0; 
        try {
            result = BitwiseAdd::bitwiseAdd(a, b);
            if (result != a + b) {
                std::cerr << "Error[" << i << "]: " << a << " * " << b << " != " << result << std::endl;
                return 1;
            }
            std::cout << a << " * " << b << " = " << result << std::endl;
        } catch (const BitwiseAdd::InputError& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    std::cout << "bitwiseAdd is working correctly" << std::endl;
    return 0;
}
