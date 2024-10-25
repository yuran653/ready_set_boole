#ifndef CNF_HPP
#define CNF_HPP

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include <memory>


class CNF {
    private:
        CNF() = delete;
        ~CNF() = delete;
    public:
        static std::string toCNF(const std::string& formula);
};

#endif
