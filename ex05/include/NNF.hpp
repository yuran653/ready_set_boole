#ifndef NNF_HPP
#define NNF_HPP

#include <iostream>
#include <stack>
#include "Node.hpp"

class NNF {
    protected:
        const std::string _formula;
        std::unique_ptr<Node> _root;
        std::string _nnf_rpn;

        NNF() = delete;
        NNF(const NNF& other) = delete;
        NNF(const NNF&& other) = delete;

        NNF& operator=(NNF& other) = delete;
        NNF& operator=(NNF&& other) = delete;

        const std::string& _remove_redundant_negation_str(std::string& input);
        std::unique_ptr<Node> _build_ast();
        bool _is_nnf(const Node* node) const;
        void _to_nnf(Node* root);
        void _to_rpn(const Node* root, std::string& formula);

    public:
        explicit NNF(std::string& formula);
        virtual ~NNF() = default;

        void print_ast(const Node* node, const std::string& prefix = "") const;
        const std::string& get_formula() const;
        const std::string& get_nnf() const;
};

#endif
