#include "Node.hpp"

Node::Node(const std::string& token) :
    _type(OPERAND),
    _token(token),
    _left(nullptr),
    _right(nullptr) {
}

Node::Node(const std::string& token, const Node& left) :
    _type(UNARY),
    _token(token),
    _left(std::make_unique<Node>(left)),
    _right(nullptr) {
    if (!_left)
        throw std::invalid_argument("Left node cannot be nullptr");
}

Node::Node(const std::string& token, const Node& left, const Node& right) :
    _type(BINARY),
    _token(token),
    _left(std::make_unique<Node>(left)),
    _right(std::make_unique<Node>(right)) {
    if (!_left || !_right)
        throw std::invalid_argument("Left or/and right nodes cannot be nullptr");
}

Node::Node(const std::string& token, std::unique_ptr<Node>&& left) :
    _type(UNARY),
    _token(token),
    _left(std::move(left)),
    _right(nullptr) {
    if (!_left)
        throw std::invalid_argument("Left node cannot be nullptr");
}

Node::Node(const std::string& token, std::unique_ptr<Node>&& left, std::unique_ptr<Node>&& right) :
    _type(BINARY),
    _token(token),
    _left(std::move(left)),
    _right(std::move(right)) {
    if (!_left || !_right)
        throw std::invalid_argument("Left or/and right nodes cannot be nullptr");
}

Node::Node(const Node& other) :
    _type(other._type),
    _token(other._token),
    _left(other._left ? std::make_unique<Node>(*other._left) : nullptr),
    _right(other._right ? std::make_unique<Node>(*other._right) : nullptr) {
}

Node::Node(Node&& other) noexcept :
    _type(other._type),
    _token(other._token),
    _left(std::move(other._left)),
    _right(std::move(other._right)) {
}

const NodeType& Node::get_type() const {
    return _type;
}

const std::string& Node::get_token() const {
    return _token;
}

const std::unique_ptr<Node>& Node::get_left() const {
    return _left;
}

const std::unique_ptr<Node>& Node::get_right() const {
    return _right;
}

std::unique_ptr<Node>& Node::get_left() {
    return _left;
}
std::unique_ptr<Node>& Node::get_right() {
    return _right;
}

void Node::set_type(const NodeType& type) {
    _type = type;
}

void Node::set_token(const std::string& token) {
    _token = token;
}

void Node::set_left(std::unique_ptr<Node> left) {
    _left = std::move(left);
}

void Node::set_right(std::unique_ptr<Node> right) {
    _right = std::move(right);
}
