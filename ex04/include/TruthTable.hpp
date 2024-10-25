#ifndef TRUTHTABLE_HPP
#define TRUTHTABLE_HPP

#include <algorithm>
#include <bitset>
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <vector>

class TruthTable {
    private:
        TruthTable() = delete;
        ~TruthTable() = delete;

    public:
        static void truthTable(const std::string& formula);
};

#endif
