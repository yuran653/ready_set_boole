#include "AST.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::pair<std::string, std::string>> formulas = {
        // {"AB&!", "A!B!|"},
        // {"AB|!", "A!B!&"},
        // {"AB>", "A!B|"},
        // {"AB=", "AB&A!B!&|"},
        // {"AB|C&!", "A!B!&C!|"},
        {"AB>!", "B!A&"}
    };
    for (std::pair<std::string, std::string> formula : formulas) {
        // std::cout << "Formula: " << formula.first << std::endl;
        // AST tree(formula.first);
        std::cout << "Formula: " << formula.first << std::endl;
        try {
            AST tree(formula.first);
            std::cout << "==== Original tree ====" << std::endl;
            tree.print_ast(tree.get_root().get());
            std::cout << "========================" << std::endl;
            // tree.preorder_traversal_iterative(tree.get_root().get());
            tree.to_nnf(tree.get_root().get());
            std::cout << "==== Converted tree ====" << std::endl;
            tree.print_ast(tree.get_root().get());
            std::cout << "========================" << std::endl;
            // std::cout << (tree.is_nnf(tree.get_root().get()) ? "True" : "False") << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}
