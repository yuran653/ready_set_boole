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
        static std::pair<std::string, std::vector<bool>> truth_table(const std::string& formula);
};

#endif
