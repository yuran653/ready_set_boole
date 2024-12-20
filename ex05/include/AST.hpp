#ifndef AST_HPP
#define AST_HPP

#include <stack>
#include <string>
#include "Node.hpp"

class AST {
    private:
        const std::string _formula;
        std::unique_ptr<Node> _root;
        std::string _nnf_rpn;

        AST() = delete;
        AST(const AST& other) = delete;
        AST(const AST&& other) noexcept;

        AST& operator=(AST& other) = delete;
        AST& operator=(AST&& other) = delete;

        const std::string& _remove_redundant_negation_str(std::string& input);
        std::unique_ptr<Node> _build_ast();
        bool _is_nnf(const Node* node) const;
        void _to_nnf(Node* root);
        void _to_rpn(const Node* root);

    public:
        explicit AST(std::string& formula);
        ~AST() = default;

        void print_ast(const Node* node, const std::string& prefix = "") const;
        const std::string& get_formula() const;
        const std::string& get_nnf() const;
};

#endif
