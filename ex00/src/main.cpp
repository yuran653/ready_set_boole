#include "BitwiseAdd.hpp"

int main() {
    try {
        std::cout << "bitwiseAdd(5, 2) = " << BitwiseAdd::bitwiseAdd(5, 2) << std::endl;
        std::cout << "bitwiseAdd(23, 4) = " << BitwiseAdd::bitwiseAdd(23, 4) << std::endl;
        std::cout << "bitwiseAdd(-5, 2) = " << BitwiseAdd::bitwiseAdd(-5, 2) << std::endl; // This will throw an exception
    } catch (const BitwiseAdd::InputError& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
