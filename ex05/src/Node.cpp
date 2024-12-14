#include "Node.hpp"
#include <iostream>

Node::Node(const char& token) :
    _type(OPERAND),
    _token(token),
    _left(nullptr),
    _right(nullptr) {
    std::cout << "Single parameter. Token [" << _token << "]" << std::endl;
    std::cout << "-----------------------------" << std::endl;
}

Node::Node(const char& token, std::unique_ptr<Node> left) :
    _type(UNARY),
    _token(token),
    _left(std::move(left)),
    _right(nullptr) {
    std::cout << "Two parameters" << std::endl;
    std::cout << "Token: [" << _token << "]" << std::endl;
    std::cout << "Left: [" << _left->get_token() << "]" << std::endl;    
    std::cout << "-----------------------------" << std::endl;
    if (!_left)
        throw std::invalid_argument("Left node cannot be nullptr");
}

Node::Node(const char& token, std::unique_ptr<Node> left, std::unique_ptr<Node> right) :
    _type(BINARY),
    _token(token),
    _left(std::move(left)),
    _right(std::move(right)) {
    std::cout << "three parameters" << std::endl;
    std::cout << "Token: [" << _token << "]" << std::endl;
    std::cout << "Left: [" << _left->get_token() << "]" << std::endl;
    std::cout << "Right: [" << _right->get_token() << "]" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    if (!_left || !_right)
        throw std::invalid_argument("Left or/and right nodes cannot be nullptr");
}

Node::Node(Node&& other) noexcept :
    _type(std::move(other._type)),
    _token(std::move(other._token)),
    _left(std::move(other._left)),
    _right(std::move(other._right)) {
}

const NodeType& Node::get_type() const {
    return _type;
}

const char& Node::get_token() const {
    return _token;
}

const std::unique_ptr<Node>& Node::get_left() const {
    return _left;
}

const std::unique_ptr<Node>& Node::get_right() const {
    return _right;
}
