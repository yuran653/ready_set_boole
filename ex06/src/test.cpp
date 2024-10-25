#include <iostream>
#include "CNF.hpp"

int main() {
    std::vector<std::string> formulas = {
        "AB&!",      // A!B!|
        "AB|!",      // A!B!&
        "AB|C&",     // AB|C&
        "AB|C|D|",   // ABCD|||
        "AB&C&D&",   // ABCD&&&
        "AB&!C!|",   // A!B!C!||
        "AB|!C!&"    // A!B!C!&&
    };

    for (const auto& formula : formulas) {
        try {
            std::cout << "Input: " << formula << " -> Output: " << CNF::toCNF(formula) << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error for formula " << formula << ": " << e.what() << std::endl;
        }
    }
    return 0;
}
