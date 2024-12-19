#include "AST.hpp"
#include <iostream>
#include <vector>

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
        // std::cout << "Formula: " << formula.first << std::endl;
        try {
            AST tree(formula.first);
            // std::cout << "==== Original tree ====" << std::endl;
            // tree.print_ast(tree.get_root().get());
            // std::cout << "========================" << std::endl;
            std::string nnf(tree.to_nnf(tree.get_root().get()));
            // std::cout << "==== Converted tree ====" << std::endl;
            // tree.print_ast(tree.get_root().get());
            // std::cout << "========================" << std::endl;
            std::cout << "Formula: " << formula.first << " shoud be " << formula.second
                << " is " << nnf << ((nnf == formula.second) ? " : OK" : " : KO") << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}
