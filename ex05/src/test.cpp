#include "AST.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::pair<std::string, std::string>> formulas = {
        {"AB&!", "A!B!|"},
        {"AB|!", "A!B!&"},
        {"AB>", "A!B|"},
        {"AB=", "AB&A!B!&|"},
        {"AB|C&!", "A!B!&C!|"}
    };
    for (std::pair<std::string, std::string> formula : formulas) {
        std::cout << "Formula: " << formula.first << std::endl;
        AST tree(formula.first);
        if (tree.is_valid() == false)
            return 1;
        tree.print_ast(tree.get_root().get());
        std::cout << tree.is_nnf(tree.get_root().get()) << std::endl;
    }
    return 0;
}
