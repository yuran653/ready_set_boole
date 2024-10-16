#include "TruthTable.hpp"

int main() {
    std::vector<std::string> test_cases = {
        "aA&C|",
        "AB|c&",
        "aB|A&",
        "A!a&C|",
        "Ab!A|&",
        "A!Aa|&",
        "Ab&a|",
        "abC|&!",
        "A!b!C|&",
        "aB&C!|",
        "AB&c|!",
        "ab&!C!",
        "a!b!C!&",
        "ab|^",
        "A!B&c^",
        "ab|C>!",
        "aB&C=!",
        "A!bc&|",
        "Ab|c&!",
        "A!b|c^",
        "A!Bc|^",
        "Ab&C=!",
        "a!bc|>",
        "A!b&c=^",
        "Ab&C>^",
        "A!b|c&=",
        "a!BC|&>",
        "Ab&c^|",
        "A!bc&^>",
        "aB&C|=!",
        "AX&C|",
        "Ab@C|",
        "A#b|C&"
    };

    for (const auto& formula : test_cases) {
        std::cout << "Truth table for formula: " << formula << std::endl;
        try {
            TruthTable::truthTable(formula);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
