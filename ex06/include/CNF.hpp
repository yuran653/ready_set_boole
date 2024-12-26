#ifndef CNF_HPP
#define CNF_HPP

#include "NNF.hpp"
#include <iostream> // remove as redundant
#include <queue>

class CNF : public NNF {
    private:
        std::string _cnf_rpn;

        CNF() = delete;
        CNF(const CNF& other) = delete;
        CNF(const CNF&& other) = delete;

        CNF& operator=(CNF& other) = delete;
        CNF& operator=(CNF&& other) = delete;

        bool _is_cnf(const Node* root) const;
        void _to_cnf(Node* root);

    public:
        explicit CNF(std::string& formula);
        ~CNF() = default;

        const std::string& get_cnf() const;
};

#endif