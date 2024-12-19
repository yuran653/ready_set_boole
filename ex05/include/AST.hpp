#ifndef AST_HPP
#define AST_HPP

#include <stack>
#include <string>
#include "Node.hpp"

class AST {
    private:
        const std::string _formula;
        std::unique_ptr<Node> _root;
        std::string _nnf;

        AST() = delete;
        AST(const AST& other) = delete;
        AST(const AST&& other) noexcept;

        AST& operator=(AST& other) = delete;
        AST& operator=(AST&& other) = delete;

        const std::string& _remove_redundant_negation_str(std::string& input);
        std::unique_ptr<Node> _build_ast(const std::string& formula);
        bool _is_nnf(const Node* node) const;
        const std::string& _to_nnf(Node* root);

    public:
        explicit AST(std::string& formula);
        ~AST() = default;

        // const std::unique_ptr<Node>& get_root() const;
        void print_ast(const Node* node, const std::string& prefix = "") const;
        const std::string& get_nnf() const;
};

#endif
