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

        std::string _remove_redundant_negitiation(const std::string& input);
        std::unique_ptr<Node> _build_ast(const std::string& formula);

    public:
        explicit AST(const std::string& formula);
        ~AST() = default;

        const std::unique_ptr<Node>& get_root() const;
        void preorder_traversal(const Node* node) const;
        void print_ast(const Node* node, const std::string& prefix = "") const;
        bool is_nnf(const Node* node) const;
        void preorder_traversal_iterative(const Node* root) const;
        void to_nnf(Node* root);
};

#endif
