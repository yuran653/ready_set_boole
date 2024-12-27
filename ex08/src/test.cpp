#include "PowerSet.hpp"

int main() {
    std::set<int32_t> input_set = {42, 1, 2, 21, 3, 42};
    try {
        PowerSet power_set(input_set);
        power_set.print_original_set();
        power_set.print_powerset();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
