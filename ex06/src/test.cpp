#include <iostream>
#include "CNF.hpp"

int main() {
    std::vector<std::vector<std::string>> formula_cases = {
        {"AB&!", "A!B!|"},
        {"AB|!", "A!B!&"},
        {"AB|C&", "AB|C&"},
        {"AB|C|D|", "ABCD|||"},
        {"AB&C&D&", "ABCD&&&"},
        {"AB&!C!|", "A!B!C!||"},
        {"AB|!C!&", "A!B!C!&&"},
        {"ABCD&|&", "ABC|BD|&&"}
    };

    for (const std::vector<std::string>& formula_case : formula_cases) {
        try {
            const std::string& input_formula = formula_case[0];
            const std::string& expected_output = formula_case[1];
            std::string actual_output = CNF::toCNF(input_formula);
            
            if (actual_output == expected_output) {
                std::cout << "Input: " << input_formula << " -> Output: " << actual_output 
                        << " [success]" << std::endl;
            } else {
                std::cout << "Input: " << input_formula << " -> Output: " << actual_output 
                        << " [failure: expected " << expected_output << "]" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error for formula " << formula_case[0] << ": " << e.what() << std::endl;
        }
    }
    return 0;
}
