#include "Curve.hpp"
#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"
#define OK "\xE2\x9C\x85"
#define KO "\xE2\x9D\x8C"

int main() {
    std::vector<std::pair<uint16_t, uint16_t>> test_cases = {
        {0, 0},
        {65535, 65535},
        {32768, 0},
        {0, 32768},
        {1, 2},
        {2, 1}
    };

    // Set output precision for floating-point values
    std::cout << std::fixed << std::setprecision(16);

    for (const auto& test : test_cases) {
        uint16_t x = std::get<0>(test);
        uint16_t y = std::get<1>(test);
        double z = Curve::map(x, y);
        std::pair<uint16_t, uint16_t> x_y = Curve::inverse_map(z);
        std::cout << "X: [" << x << "], Y: [" << y << "] -> "
                      << "Mapped value: " << z
                      << " -> Inversed X: [" << x_y.first
                      << "], Inversed Y: [" << x_y.second << "]";
        if (x == x_y.first && y == x_y.second) {
            std::cout << GREEN << " OK " << RESET << OK;
        } else {
            std::cout << RED << " KO " << RESET << KO;
        }
        std::cout << std::endl;
    }
    return 0;
}
