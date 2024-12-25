#include "CNF.hpp"
#include <iostream>
#include <vector>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"
#define OK "\xE2\x9C\x85"
#define KO "\xE2\x9D\x8C"

int main() {
    std::vector<std::pair<std::string, std::string>> formulas = {
        {"AB&!", "A!B!|"}, // OK
        {"AB|!", "A!B!&"}, // OK
        {"AB|C&", "AB|C&"}, // OK
        {"AB|C|D|", "ABCD|||"}, // OK
        {"AB&C&D&", "ABCD&&&"}, // OK
        {"AB&!C!|", "A!B!C!||"}, // OK
        {"AB|!C!&", "A!B!C!&&"}, // OK
        {"ABCD&|&", "ABC|BD|&&"}, // OK
        {"ABC&|", "AB|AC|&"}, // OK
        {"AB&C|", "AC|BC|&"}, // OK
        {"AB&CD&|", "AC|AD|BC|BD|&&&"}, // OK
    };
    for (std::pair<std::string, std::string> formula : formulas) {
        try {
            CNF tree(formula.first);
            std::cout << "Formula: " << formula.first << " should be " << formula.second
                << " -> result " <<  tree.get_cnf();
            if ((tree.get_cnf() == formula.second))
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
