#include "NNF.hpp"
#include <vector>

int main() {
    std::vector<std::string> formulas = {
        "AB&!",     // ¬(A ∧ B) -> A!B!|
        "AB|!",     // ¬(A ∨ B) -> A!B!&
        "AB>",      // A!B|
        "AB=",      // AB&A!B!&|
        "A!",       // ¬A -> A!
        "ABC&&!",   // ¬(A ∧ B ∧ C) -> A!B!|C!|
        "AB|C&!",   // ¬((A ∨ B) ∧ C) -> A!B!&C!|
        "A",        // A
        "&",        // Invalid formula: not enough operands for binary operator
        "AB&&",     // Invalid formula: not enough operands for binary operator
        "A|B",      // Invalid formula: not enough operands for binary operator
        "AB!="
    };
    for (const auto& formula : formulas) {
        try {
            std::cout << "Input: " << formula << " -> Output: " << NNF::toNNF(formula) << std::endl;
        } catch(const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}
