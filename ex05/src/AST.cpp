#include "AST.hpp"
#include <iostream>

AST::AST(std::string& formula) :
    _formula(_remove_redundant_negation_str(formula)),
    _root(_build_ast(_remove_redundant_negation_str(formula))) {
    if (_root == nullptr)
        throw std::runtime_error("Invalid formula / Unable to build AST");
    _nnf = _to_nnf(_root.get());
}

const std::string& AST::_remove_redundant_negation_str(std::string& input) {
    size_t position = input.find("!!");
    while (position != std::string::npos) {
        input.erase(position, 2);
        position = input.find("!!");
    }
    return input;
}

std::unique_ptr<Node> AST::_build_ast(const std::string& formula) {
    try {
        std::stack<std::unique_ptr<Node>> stack;
        std::unique_ptr<Node> tmp_right;
        std::unique_ptr<Node> tmp_left;
        for (char token : formula) {
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
                    stack.push(std::make_unique<Node>(token, std::move(tmp_left), std::move(tmp_right)));
                    break;
                default:
                    throw std::invalid_argument("Invalid character in formula");
            }
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

// const std::unique_ptr<Node>& AST::get_root() const {
//     return _root;
// }

bool AST::_is_nnf(const Node* node) const {
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
        if (node->get_token() == '&' || node->get_token() == '|')
            return _is_nnf(node->get_left().get()) && _is_nnf(node->get_right().get());
    }
    return false;
}

static void handle_binary(Node* root) {
    if (root == nullptr)
        return;
    std::stack<Node*> stack;
    stack.push(root);
    while (!stack.empty()) {
        Node* node = stack.top();
        stack.pop();
        if (node->get_type() == BINARY &&
            (node->get_token() == '>' || node->get_token() == '=' || node->get_token() == '^')) {
            std::unique_ptr<Node> saved_tree = std::make_unique<Node>(node->get_left()->get_token(),
                std::move(node->get_left()), std::move(node->get_right()));
            switch (node->get_token()) {
                case '>':
                    node->set_type(BINARY);
                    node->set_token('|');
                    node->set_left(std::make_unique<Node>('!', std::move(*saved_tree->get_left())));
                    node->set_right(std::make_unique<Node>(std::move(*saved_tree->get_right())));
                    break;
                case '=':
                    node->set_type(BINARY);
                    node->set_token('|');
                    node->set_left(std::make_unique<Node>('&',
                        std::make_unique<Node>(*saved_tree->get_left()),
                        std::make_unique<Node>(*saved_tree->get_right())));
                    node->set_right(std::make_unique<Node>('&',
                        std::make_unique<Node>('!', *saved_tree->get_left()),
                        std::make_unique<Node>('!', *saved_tree->get_right())));
                    saved_tree.reset();
                    break;
                case '^':
                    node->set_type(BINARY);
                    node->set_token('|');
                    node->set_left(std::make_unique<Node>('&',
                        std::make_unique<Node>(*saved_tree->get_left()),
                        std::make_unique<Node>('!',*saved_tree->get_right())));
                    node->set_right(std::make_unique<Node>('&',
                        std::make_unique<Node>('!', *saved_tree->get_left()),
                        std::make_unique<Node>(*saved_tree->get_right())));
                    saved_tree.reset();
                    break;
                default:
                    throw std::runtime_error("Invalid binary token");
            }
        }
        if (node->get_right() != nullptr)
            stack.push(node->get_right().get());
        if (node->get_left() != nullptr)
            stack.push(node->get_left().get());
    }
}

static void handle_unary(Node* root) {
    if (root == nullptr)
        return;
    std::stack<Node*> stack;
    stack.push(root);
    while (!stack.empty()) {
        Node* node = stack.top();
        stack.pop();
        if (node->get_type() == UNARY && node->get_left()->get_type() == BINARY) {
            std::unique_ptr<Node> saved_tree = std::make_unique<Node>(node->get_left()->get_token(),
                std::move(node->get_left()->get_left()), std::move(node->get_left()->get_right()));
            switch (node->get_left()->get_token()) {
                case '&':
                    node->set_type(BINARY);
                    node->set_token('|');
                    node->set_left(std::make_unique<Node>('!', std::move(saved_tree->get_left())));
                    node->set_right(std::make_unique<Node>('!', std::move(saved_tree->get_right())));
                    break;
                case '|':
                    node->set_type(BINARY);
                    node->set_token('&');
                    node->set_left(std::make_unique<Node>('!', std::move(saved_tree->get_left())));
                    node->set_right(std::make_unique<Node>('!', std::move(saved_tree->get_right())));
                    break;
                default:
                    throw std::runtime_error("Invalid binary token");
            }
        }
        if (node->get_right() != nullptr)
            stack.push(node->get_right().get());
        if (node->get_left() != nullptr)
            stack.push(node->get_left().get());
    }
}

static void remove_redundant_negation_ast(Node* root) {
    if (root == nullptr)
        return;
    std::stack<Node*> stack;
    stack.push(root);
    while (!stack.empty()) {
        Node* node = stack.top();
        stack.pop();
        if (node->get_type() == UNARY && node->get_left() && node->get_left()->get_type() == UNARY) {
            if (node->get_left()->get_left() != nullptr) {
                std::unique_ptr<Node> operand_node = std::move(node->get_left()->get_left());
                node->set_type(operand_node->get_type());
                node->set_token(operand_node->get_token());
                node->set_left(operand_node->get_left() ? std::make_unique<Node>(*operand_node->get_left()) : nullptr);
                node->set_right(operand_node->get_right() ? std::make_unique<Node>(*operand_node->get_right()) : nullptr);
            }
        }
        if (node->get_right() != nullptr)
            stack.push(node->get_right().get());
        if (node->get_left() != nullptr)
            stack.push(node->get_left().get());
    }
}

static void to_rpn(const Node* root, std::string& result) {
    if (root == nullptr)
        return;
        
    // For operands, just append the token
    if (root->get_type() == OPERAND) {
        result += root->get_token();
        return;
    }
    
    // For unary operators (NOT), traverse left child then append operator
    if (root->get_type() == UNARY) {
        to_rpn(root->get_left().get(), result);
        result += root->get_token();
        return;
    }
    
    // For binary operators, traverse both children then append operator
    if (root->get_type() == BINARY) {
        to_rpn(root->get_left().get(), result);
        to_rpn(root->get_right().get(), result);
        result += root->get_token();
        return;
    }
}

const std::string& AST::_to_nnf(Node* root) {
    if (_is_nnf(root))
        return _formula;
    handle_binary(root);
    handle_unary(root);
    remove_redundant_negation_ast(root);
    if (_is_nnf(root) == false)
        throw std::logic_error("Wrong conversion to NNF");
    static std::string result;
    result.clear();
    to_rpn(root, result);
    return result;
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

const std::string& AST::get_nnf() const {
    return _nnf;
}
