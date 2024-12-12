#ifndef NNF_HPP
#define NNF_HPP

#include <stdexcept>
#include <cctype>
#include <stack>
#include <string>

class NNF {
    private:
        NNF() = delete;
        ~NNF() = delete;

    public:
        static std::string toNNF(const std::string& formula);
};

#endif