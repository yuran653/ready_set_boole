#include "AST.hpp"

AST::AST(const std::string& formula) :
    _formula(formula),
    _root(_build_ast(formula)) {
}

const std::unique_ptr<Node> AST::_build_ast(const std::string& formula) const {
    std::stack<std::unique_ptr<Node>> stack;
    for (char token : formula) {
        switch (token) {
            case 'A' ... 'Z':
                stack.push(std::make_unique<Node>(token));
                break;
            case '!':
                std::unique_ptr<Node> tmp = std::move(stack.top());
                stack.pop();
                stack.push(std::make_unique<Node>(token, std::move(tmp)));
                break;
            // case '&':
            // case '|':
            // case '>':
            // case '=':
            // case '^':
            //     if (stack.size() < 2)
            //         throw std::runtime_error("Invalid formula: not enough operands for binary operator");
            //     root = std::make_unique<Node>(token, std::make_unique<Node>(stack.top()), std::make_unique<Node>(stack.top()));

    }
}

const Node* AST::get_root() const {
    return _root.get();
}
