#include "ASTnode.hpp"

ASTnode::ASTnode() : _left(nullptr), _right(nullptr), _token("") {
}

ASTnode::ASTnode(ASTnode&& other) noexcept :
        _left(std::move(other._left)),
        _right(std::move(other._right)),
        _token(std::move(other._token)) {
}

ASTnode ASTnode::build_ast(const std::string& token, const ssize_t i) {
    if (i < 0 || i >= static_cast<ssize_t>(token.size()))
        throw std::out_of_range("Index out of bounds in build_ast");
    ASTnode node;
    node._left = std::make_unique<ASTnode>();
    node._right = std::make_unique<ASTnode>();
    size_t right_size = 0;
    switch (token.at(i)) {
        case '!':
            node._left->_token = token.substr(i - 1, 1);
            node._token = node._left->_token + token.at(i);
            return node;
        case '&':
        case '|':
        case '>':
        case '=':
        case '^':
            node._right = std::make_unique<ASTnode>(build_ast(token, i - 1));
            right_size = node._right->_token.size();
            node._left = std::make_unique<ASTnode>(build_ast(token, i - 1 - right_size));
            node._token = node._left->_token + node._right->_token + token.at(i);
            return node;
        default:
            node._token = token.substr(i, 1);
            return node;
    }
}

const std::unique_ptr<ASTnode>& ASTnode::get_left() const {
    return _left;
}
const std::unique_ptr<ASTnode>& ASTnode::get_right() const {
    return _right;
 }

 const std::string& ASTnode::get_token() const {
    return _token;
}
