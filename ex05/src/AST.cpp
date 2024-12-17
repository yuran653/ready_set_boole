#include "AST.hpp"
#include <iostream>

AST::AST(const std::string& formula) :
    _formula(formula), _root(_build_ast(formula)) {
}

std::unique_ptr<Node> AST::_build_ast(const std::string& formula) {
    try {
        // std::cout << "BUILDING AST" << std::endl;
        std::stack<std::unique_ptr<Node>> stack;
        std::unique_ptr<Node> tmp_right;
        std::unique_ptr<Node> tmp_left;
        for (char token : formula) {
            // std::cout << "AST token [" << token << "]" << std::endl;
            switch (token) {
                case 'A' ... 'Z':
                    stack.push(std::make_unique<Node>(token));
                    break;
                case '!':
                    tmp_right = std::move(stack.top());
                    stack.pop();
                    stack.push(std::make_unique<Node>(token, std::move(tmp_right)));
                    break;
                case '&':
                case '|':
                case '>':
                case '=':
                case '^':
                    if (stack.size() < 2)
                        throw std::runtime_error("Invalid formula: not enough operands for binary operator");
                    tmp_right = std::move(stack.top());
                    stack.pop();
                    tmp_left = std::move(stack.top());
                    stack.pop();
                    // std::cout << "Temp right [" << tmp_right->get_token() << "]" << std::endl;
                    // std::cout << "Temp left [" << tmp_left->get_token() << "]" << std::endl;
                    stack.push(std::make_unique<Node>(token, std::move(tmp_left), std::move(tmp_right)));
                    break;
                default:
                    throw std::invalid_argument("Invalid character in formula");
            }
            // std::cout << "Stack size: " << stack.size() << " after token [" << token << "]" << std::endl << std::endl;
        }
        if (stack.size() != 1)
            throw std::runtime_error("Invalid formula: incorrect number of operands/operators in formula");
        std::unique_ptr<Node> root = std::move(stack.top());
        stack.pop();
        return root;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return nullptr;
    }
}

const std::unique_ptr<Node>& AST::get_root() const {
    return _root;
}

bool AST::is_valid() const {
    return _root != nullptr;
}

void AST::preorder_traversal(const Node* node) const {
    if (node == nullptr)
        return;
    std::cout << "Token: [" << node->get_token() << "]" << std::endl;
    preorder_traversal(node->get_left().get());
    preorder_traversal(node->get_right().get());
}

void AST::print_ast(const Node* node, const std::string& prefix) const {
    if (node == nullptr)
        return;

    std::cout << prefix << "`-- " << node->get_token() << std::endl;

    switch (node->get_type()) {
        case UNARY:
            print_ast(node->get_left().get(), prefix + "    ");
            break;
        case BINARY:
            print_ast(node->get_left().get(), prefix + "    ");
            print_ast(node->get_right().get(), prefix + "    ");
            break;
        default:
            break;
    }
}

std::string AST::is_nnf(const Node* node, std::string tokens) const {
    if (node == nullptr)
        return tokens;
    if (node->get_type() != OPERAND)
        tokens += std::to_string(node->get_token());
    is_nnf(node->get_left().get(), tokens);
    is_nnf(node->get_right().get(), tokens);
    return tokens;
}
