#include "NNF.hpp"
#include <iostream>
#include <vector>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"
#define OK "\xE2\x9C\x85"
#define KO "\xE2\x9D\x8C"

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
            NNF tree(formula.first);
            std::cout << "Formula: " << formula.first << " should be " << formula.second
                << " is " << tree.get_nnf();
                if ((tree.get_nnf() == formula.second))
                std::cout << GREEN << " OK " << RESET << OK;
                else
                    std::cout << RED << " KO " << RESET << KO;
                std::cout << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}
