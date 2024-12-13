#include "NNF.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<std::vector<std::string>> formulas = {
        {"AB&!", "A!B!|"},
        {"AB|!", "A!B!&"},
        {"AB>", "A!B|"},
        {"AB=", "AB&A!B!&|"},
        {"AB|C&!", "A!B!&C!|"}
    };
    for (const auto& formula : formulas) {
        try {
            std::cout << "Input: " << formula[0] << " ";
            std::string nnf = NNF::toNNF(formula[0]);
            std::cout << "-> Output: " << nnf;
            if (nnf == formula[1])
                std::cout << " [success]" << std::endl;
            else
                std::cout << " [failure: expected \"" << formula[1] << "\"]" << std::endl;
        } catch(const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}
