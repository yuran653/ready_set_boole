#ifndef AST_HPP
#define AST_HPP

#include <stack>
#include <string>
#include "Node.hpp"

class AST {
    private:
        const std::string _formula;
        std::unique_ptr<Node> _root;

        AST() = delete;
        AST(const AST& other) = delete;
        AST(const AST&& other) noexcept;

        AST& operator=(AST& other) = delete;
        AST& operator=(AST&& other) = delete;

        std::unique_ptr<Node> _build_ast(const std::string& formula);

    public:
        explicit AST(const std::string& formula);
        ~AST() = default;

        const std::unique_ptr<Node>& get_root() const;
};

#endif
