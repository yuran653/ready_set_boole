#include "CNF.hpp"
#include <iostream>
#include <vector>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

int main() {
    std::vector<std::pair<std::string, std::string>> formulas = {
        // {"AB&!", "A!B!|"}, // OK
        // // {"A!B!|", "-> TREE CHECK <-"},
        // {"AB|!", "A!B!&"}, // OK
        // // {"A!B!&", "-> TREE CHECK <-"},
        // {"AB|C&", "AB|C&"}, // OK
        // // {"AB|C&", "-> TREE CHECK <-"},
        // {"AB|C|D|", "ABCD|||"}, // OK
        // // {"ABCD|||", "-> TREE CHECK <-"},
        // {"AB&C&D&", "ABCD&&&"}, // OK
        // // {"ABCD&&&", "-> TREE CHECK <-"},
        // {"AB&!C!|", "A!B!C!||"}, // OK
        // // {"A!B!C!||", "-> TREE CHECK <-"},
        // {"AB|!C!&", "A!B!C!&&"}, // OK
        // // {"A!B!C!&&", "-> TREE CHECK <-"},
        // {"ABCD&|&", "ABC|BD|&&"}, // OK
        // // {"ABC|BD|&&", "-> TREE CHECK <-"},
        // {"ABC&|", "AB|AC|&"}, // OK
        // // {"AB|AC|&", "-> TREE CHECK <-"},
        // {"AB&C|", "AC|BC|&"}, // KO
        // // {"AC|BC|&", "-> TREE CHECK <-"},
        {"AB&CD&|", "AC|AD|&BC|BD|&&"}, // KO
        {"AC|AD|&BC|BD|&&", "-> TREE CHECK <-"}
    };
    for (std::pair<std::string, std::string> formula : formulas) {
        try {
            CNF tree(formula.first);
            std::cout << "Formula: " << formula.first << " should be " << formula.second
                << " -> result " <<  tree.get_cnf();
            if ((tree.get_cnf() == formula.second))
                std::cout << GREEN << " OK ✅" << RESET;
            else
                std::cout << RED << " KO ❌" << RESET;
        std::cout << std::endl;
        std::cout << "================================================" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}
