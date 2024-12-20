#include "AST.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::pair<std::string, std::string>> formulas = {
        {"AB&!", "A!B!|"},
        {"AB|!", "A!B!&"},
        {"AB>", "A!B|"},
        {"AB=", "AB&A!B!&|"},
        {"AB|C&!", "A!B!&C!|"},
        {"AB>!", "AB!&"}
    };
    for (std::pair<std::string, std::string> formula : formulas) {
        try {
            AST tree(formula.first);
            std::cout << "Formula: " << formula.first << " should be " << formula.second
                << " is " << tree.get_nnf() << ((tree.get_nnf() == formula.second) ? " : OK" : " : KO") << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}
