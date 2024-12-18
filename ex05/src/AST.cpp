#include "AST.hpp"
#include <iostream>

AST::AST(const std::string& formula) :
    _formula(_remove_redundant_negitiation(formula)),
    _root(_build_ast(_remove_redundant_negitiation(formula))) {
    if (_root == nullptr)
        throw std::runtime_error("Invalid formula / Unable to build AST");
}

std::string AST::_remove_redundant_negitiation(const std::string& input) {
    std::string result(input);
    size_t position = result.find("!!");
    while (position != std::string::npos) {
        result.erase(position, 2);
        position = result.find("!!");
    }
    return result;
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
                    if (stack.size() < 1)
                        throw std::runtime_error("Invalid formula: not enough operands for unary operator");
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

void AST::preorder_traversal_iterative(const Node* root) const {
    if (root == nullptr) {
        return;
    }

    std::stack<const Node*> stack;
    stack.push(root);
    int iter = 0;
    while (!stack.empty()) {
        const Node* node = stack.top();
        stack.pop();

        // Process the current node
        std::cout << "Token: [" << node->get_token() << "]" << std::endl;

        // Push right child first so that the left child is processed first
        if (node->get_right() != nullptr) {
            stack.push(node->get_right().get());
        }
        if (node->get_left() != nullptr) {
            stack.push(node->get_left().get());
        }
        std::cout << "Iteration [" << ++iter << "] passed" << std::endl;
    }
}


bool AST::is_nnf(const Node* node) const {
    if (node == nullptr)
        return true;
    if (node->get_type() == OPERAND)
        return true;
    if (node->get_type() == UNARY) {
        if (node->get_token() == '!') {
            if (node->get_left().get() && node->get_left().get()->get_type() == OPERAND)
                return true;
            else
                return false;
        }
    }
    if (node->get_type() == BINARY) {
        if (node->get_token() == '&' || node->get_token() == '|') {
            return is_nnf(node->get_left().get()) && is_nnf(node->get_right().get());
        }
    }
    return false;
}

void AST::to_nnf(Node* root) {
    if (root == nullptr) {
        return;
    }

    std::stack<Node*> stack;
    stack.push(root);
    // int iter = 0;
    while (!stack.empty()) {
        Node* node = stack.top();
        stack.pop();
        // std::cout << "Token: [" << node->get_token() << "]" << std::endl;
        if (node->get_type() == UNARY && node->get_left()->get_type() == BINARY) {
            // std::cout << "Operator: [" << node->get_left()->get_token() << "]" << std::endl;
            // std::cout << "Left tree:" << std::endl;
            // print_ast(node->get_left()->get_left().get());
            // std::cout << "Right tree:" << std::endl;
            // print_ast(node->get_left()->get_right().get());
            std::unique_ptr<Node> saved_tree = std::make_unique<Node>(node->get_left()->get_token(),
                std::move(node->get_left()->get_left()), std::move(node->get_left()->get_right()));
            // std::cout << "===== Saved tree =====" << std::endl;
            // print_ast(saved_tree.get());
            // std::cout << "======================" << std::endl;
            switch (node->get_left()->get_token()) {
                case '&':
                    // std::cout << "AND -> stack size: " << stack.size() << std::endl;
                    node->set_type(BINARY);
                    node->set_token('|');
                    node->set_left(std::make_unique<Node>('!', std::move(saved_tree->get_left())));
                    node->set_right(std::make_unique<Node>('!', std::move(saved_tree->get_right())));
                    break;
                case '|':
                    // std::cout << "OR -> stack size: " << stack.size() << std::endl;
                    node->set_type(BINARY);
                    node->set_token('&');
                    node->set_left(std::make_unique<Node>('!', std::move(saved_tree->get_left())));
                    node->set_right(std::make_unique<Node>('!', std::move(saved_tree->get_right())));
                    break;
                case '>':
                    // std::cout << "IMPLICATION -> stack size: " << stack.size() << std::endl;
                    node->set_type(BINARY);
                    node->set_token('&');
                    node->set_left(std::move(saved_tree->get_left()));
                    node->set_right(std::make_unique<Node>('!', std::move(saved_tree->get_right())));
                    break;
                case '=':
                    std::cout << "IFF -> stack size: " << stack.size() << std::endl;
                    break;
                case '^':
                    std::cout << "XOR -> stack size: " << stack.size() << std::endl;
                    break;
                default:
                    throw std::runtime_error("Invalid binary token");
            }
        }
        // Push right child first so that the left child is processed first
        if (node->get_right() != nullptr) {
            stack.push(node->get_right().get());
        }
        if (node->get_left() != nullptr) {
            stack.push(node->get_left().get());
        }
        // std::cout << "Iteration [" << ++iter << "] passed" << std::endl;
    }
}
