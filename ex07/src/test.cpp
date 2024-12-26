#include "SAT.hpp"

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"
#define OK "\xE2\x9C\x85"
#define KO "\xE2\x9D\x8C"

int main() {
    std::vector<std::pair<std::string, bool>> test_cases = {
        // Valid complex cases
        {"AB|", true},
        {"AB&", true},
        {"AA!&", false},
        {"AA^", false},
        {"AB|C&", true},
        {"AB&C|", true},
        {"AB^C|", true},
        {"AB&A!&", false},
        {"AB|A!B!&&", false},

        // Invalid cases
        {"AB", false},           // Stack overflow: too many values on the stack
        {"AB&C|&&&", false},     // Stack underflow: not enough values on the stack
        {"AB#C", false}          // Invalid character '#' in formula
    };
    for (const auto& formula : test_cases) {
        try {
            bool result = SAT::sat(formula.first);
            std::cout << "The formula: " << formula.first << " is satisfiable: "
                << (result ? GREEN "true" RESET: RED "false" RESET);
            if (result == formula.second)
                std::cout << GREEN << " OK " << RESET << OK;
            else
                std::cout << RED << " KO " << RESET << KO;
        std::cout << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: sat: " << e.what() << std::endl;
        }
    }
    return 0;
}
