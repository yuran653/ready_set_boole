#include "CNF.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::pair<std::string, std::string>> formulas = {
        {"AB&!", "A!B!|"},
        {"AB|!", "A!B!&"},
        {"AB|C&", "AB|C&"},
        {"AB|C|D|", "ABCD|||"},
        {"AB&C&D&", "ABCD&&&"},
        {"AB&!C!|", "A!B!C!||"},
        {"AB|!C!&", "A!B!C!&&"},
        {"ABCD&|&", "ABC|BD|&&"}
    };
    for (std::pair<std::string, std::string> formula : formulas) {
        try {
            CNF tree(formula.first);
            std::cout << "Formula: " << formula.first << " should be " << formula.second
                << " is " << tree.get_cnf() << ((tree.get_cnf() == formula.second) ? " : OK" : " : KO") << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}
