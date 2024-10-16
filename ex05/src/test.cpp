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
        "A",        // No operator, so NNF should be A (error)
        "&",        // Missing operands
        "AB&&",     // Too many operators
    "A|B"       // Incorrect operator placement
    };
    for (const auto& formula : formulas) {
        try {
            std::cout << "Input: " << formula << " -> Output: " << NNF::toNNF(formula) << std::endl;
        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
    return 0;
}
