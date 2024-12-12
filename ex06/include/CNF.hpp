#ifndef CNF_HPP
#define CNF_HPP

#include <string>
#include <memory>
#include "ASTnode.hpp"
#include "NNF.hpp"


class CNF {
    private:
        CNF() = delete;
        ~CNF() = delete;

        static bool is_valid(const std::string& str) noexcept;
        static std::string transform_to_cnf(const std::string& str);

    public:
        static std::string toCNF(const std::string& formula);
};

#endif
