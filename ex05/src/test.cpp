#include "AST.hpp"
#include <iostream>

int main() {
    std::string formula("A!B!&C!|&");
    std::cout << formula << std::endl;
    AST tree(formula);
    return 0;
}
