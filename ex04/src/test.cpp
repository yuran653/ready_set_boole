#include "TruthTable.hpp"

int main() {
    std::vector<std::string> test_cases = {
        // Valid complex cases
        "AB&C|", // (A AND B) OR C
        "AB|C&",        // (A OR B) AND C
        "ABC&&",        // A AND B AND C
        "AB&!C|",       // (A AND B) OR (NOT C)
        "ABC||DE&|",    // ((A OR B) OR C) OR (D AND E)
        "AB&CD&|EF&|",  // ((A AND B) OR (C AND D)) OR (E AND F)
        "ABC&|DE!&|",   // ((A OR (B AND C)) OR (D AND (NOT E)))
        "AB>C!&DE|&",   // ((A IMPLIES B) AND (NOT C)) AND (D OR E)
        "AB=CD=&EF=&",  // ((A EQUALS B) AND (C EQUALS D)) AND (E EQUALS F)
        "AB^C&DE^|F&",  // ((A XOR B) AND C) OR ((D XOR E) AND F)
        
        // Invalid cases
        "AB",           // Stack overflow: too many values on the stack
        "AB&C|&&&",     // Stack underflow: not enough values on the stack
        "AB#C"          // Invalid character '#' in formula
    };
    for (const auto& formula : test_cases)
        std::cout << "The \"Truth Table\" for RPN formula: " << formula << std::endl
            << TruthTable::truth_table(formula).first << std::endl;
    return 0;
}
