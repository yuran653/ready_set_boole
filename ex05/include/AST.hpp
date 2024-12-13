#ifndef AST_HPP
#define AST_HPP

#include <stack>
#include <string>
#include "Node.hpp"

class AST {
    private:
        const std::string _formula;
        const std::unique_ptr<Node> _root;

        AST() = delete;
        AST(const AST& other) = delete;
        AST(const AST&& other) noexcept;

        AST& operator=(AST& other) = delete;
        AST& operator=(AST&& other) = delete;

        const std::unique_ptr<Node> _build_ast(const std::string& formula) const;

    public:
        explicit AST(const std::string& formula);
        ~AST() = default;

        const Node* get_root() const;
};

#endif
