#include "PowerSet.hpp"

int main() {
    std::set<int32_t> input_set = {42, 1, 2, 3};
    PowerSet power_set(input_set);
    power_set.print_original_set();
    power_set.print_powerset();
    return 0;
}
