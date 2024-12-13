#include "Node.hpp"

Node::Node(const char& token) :
    _type(OPERAND),
    _token(token),
    _left(nullptr),
    _right(nullptr) {
}

Node::Node(const char& token, std::unique_ptr<Node> left) :
    _type(UNARY),
    _token(token),
    _left(std::move(left)),
    _right(nullptr) {
    if (!_left)
        throw std::invalid_argument("Left node cannot be nullptr");
}

Node::Node(const char& token, std::unique_ptr<Node> left, std::unique_ptr<Node> right) :
    _type(BINARY),
    _token(token),
    _left(std::move(left)),
    _right(std::move(right)) {
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
