#ifndef NODE_HPP
#define NODE_HPP

#include <stdexcept>
#include <memory>

enum NodeType {
    OPERAND,
    UNARY,
    BINARY,
};

class Node {
    private:
        NodeType _type;
        char _token;
        std::unique_ptr<Node> _left;
        std::unique_ptr<Node> _right;

        Node() = delete;
        Node(const Node& other) = delete;

        Node& operator=(Node& other) = delete;
        Node& operator=(Node&& other) = delete;

    public:
        explicit Node(const char& token);
        Node(const char& token, std::unique_ptr<Node> left);
        Node(const char& token, std::unique_ptr<Node> left, std::unique_ptr<Node> right);
        Node(Node&& other) noexcept;
        ~Node() = default;

        const NodeType& get_type() const;
        const char& get_token() const;
        const std::unique_ptr<Node>& get_left() const;
        const std::unique_ptr<Node>& get_right() const;
};

#endif //NODE_HPP
