#include "SAT.hpp"

bool SAT::sat(const std::string& formula) {
    std::vector<bool> values = TruthTable::truth_table(formula).second;
    if (values.empty())
        throw std::invalid_argument("Error: invalid formula: " + formula);
    for (bool value : values)
        if (value == true)
            return true;
    return false;
}