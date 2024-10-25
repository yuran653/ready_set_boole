#include "ASTnode.hpp"

ASTnode::ASTnode(const std::string& token,
    std::unique_ptr<ASTnode> left, std::unique_ptr<ASTnode> right) :
    _left(std::move(left)), _right(std::move(right)), _token(token) {
}

ASTnode::ASTnode(const ASTnode& other) :
    _left(other._left ? std::make_unique<ASTnode>(*other._left) : nullptr),
    _right(other._right ? std::make_unique<ASTnode>(*other._right) : nullptr),
    _token(other._token) {
}

ASTnode ASTnode::build_ast(const std::string& token, const ssize_t i) {
    if (i < 0 || i >= static_cast<ssize_t>(token.size()))
        return ASTnode(token.substr(i, 1), nullptr, nullptr);
    char op = token[i];
    std::unique_ptr<ASTnode> left_node = nullptr;
    std::unique_ptr<ASTnode> right_node = nullptr;
    switch (op) {
        case '!':
            left_node = std::make_unique<ASTnode>(token.substr(i - 1, 1), nullptr, nullptr);
            return ASTnode(left_node->_token + "!", std::move(left_node), nullptr);
        case '&':
        case '|':
        case '>':
        case '=':
        case '^':
            right_node = std::make_unique<ASTnode>(build_ast(token, i - 1));
            left_node = std::make_unique<ASTnode>(build_ast(token, i - 1 - right_node->_token.length()));
            return ASTnode(left_node->_token + right_node->_token + op, std::move(left_node), std::move(right_node));
        default:
            return ASTnode(token.substr(i, 1), nullptr, nullptr);
    }
}

void ASTnode::print_ast(int depth) const {
    for (int i = 0; i < depth; ++i)
        std::cout << "    ";
    std::cout << _token << '\n';
    if (_left) _left->print_ast(depth + 1);
    if (_right) _right->print_ast(depth + 1);
}
