#include "CNF.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::pair<std::string, std::string>> formulas = {
        {"AB&!", "A!B!|"}, // OK
        {"AB|!", "A!B!&"}, // OK
        {"AB|C&", "AB|C&"}, // OK
        {"AB|C|D|", "ABCD|||"}, // KO <-
        {"AB&C&D&", "ABCD&&&"}, // KO
        {"AB&!C!|", "A!B!C!||"}, // KO
        {"AB|!C!&", "A!B!C!&&"}, // KO
        {"ABCD&|&", "ABC|BD|&&"}, // OK
        {"ABC&|", "AB|AC|&"}, // OK
        {"AB&C|", "AC|BC|&"}, // OK
        {"AB&CD&|", "AC|AD|&BC|BD|&&"} // OK
    };
    for (std::pair<std::string, std::string> formula : formulas) {
        try {
            CNF tree(formula.first);
            std::cout << "Formula: " << formula.first << " should be " << formula.second
                << " -> result " << tree.get_cnf() << ((tree.get_cnf() == formula.second) ? " : OK" : " : KO") << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}
