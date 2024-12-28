#ifndef NODE_HPP
#define NODE_HPP

#include <stdexcept>
#include <string>
#include <memory>

enum NodeType {
    OPERAND,
    UNARY,
    BINARY,
};

class Node {
    private:
        NodeType _type;
        std::string _token;
        std::unique_ptr<Node> _left;
        std::unique_ptr<Node> _right;

        Node() = delete;

        Node& operator=(Node& other) = delete;
        Node& operator=(Node&& other) = delete;

    public:
        explicit Node(const std::string& token);
        Node(const std::string& token, const Node& left);
        Node(const std::string& token, const Node& left, const Node& right);
        Node(const std::string& token, std::unique_ptr<Node>&& left);
        Node(const std::string& token, std::unique_ptr<Node>&& left, std::unique_ptr<Node>&& right);
        Node(const Node& other);
        Node(Node&& other) noexcept;
        ~Node() = default;

        const NodeType& get_type() const;
        const std::string& get_token() const;
        const std::unique_ptr<Node>& get_left() const;
        const std::unique_ptr<Node>& get_right() const;
        std::unique_ptr<Node>& get_left();
        std::unique_ptr<Node>& get_right();
        void set_type(const NodeType& type);
        void set_token(const std::string& token);
        void set_left(std::unique_ptr<Node> left);
        void set_right(std::unique_ptr<Node> right);
};

#endif
