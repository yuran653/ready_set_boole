#ifndef SAT_HPP
#define SAT_HPP

#include "TruthTable.hpp"

class SAT {
    private:
        SAT() = delete;
        ~SAT() = delete;

    public:
        static bool sat(const std::string& formula);
};

#endif
