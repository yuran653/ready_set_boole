#include "TruthTable.hpp"

bool boolean_evaluation(const std::string& rpn) {
    // Stack to hold Boolean values during evaluation
    std::stack<bool> s;
    bool a, b;
    // Iterate through each character in the formula
    for (char c : rpn) {
        if (c == '0') {
            s.push(false); // Push 'false' for literal 0
        } else if (c == '1') {
            s.push(true);  // Push 'true' for literal 1
        } else {
            // For '!', only one operand is required.
            if (c == '!' && rpn.size() > 1) {
                a = s.top(); s.pop();
            // For other operators, ensure there are at least two operands
            } else if (s.size() < 2) {
                throw std::underflow_error("Stack underflow: not enough values on the stack");
            } else {
                b = s.top(); s.pop(); // Pop the second operand
                a = s.top(); s.pop(); // Pop the first operand
            }
            // Evaluate the operator and push the result back onto the stack
            switch (c) {
                case '!':
                    s.push(!a);
                    break;
                case '&':
                    s.push(a && b);
                    break;
                case '|':
                    s.push(a || b);
                    break;
                case '^':
                    s.push(a != b); // XOR: true if operands differ
                    break;
                case '>':
                    s.push(!a || b); // Implication: A ? B : true
                    break;
                case '=':
                    s.push(a == b);
                    break;
                default:
                    throw std::invalid_argument("Invalid character in formula");
            }
        }
    }
    // Ensure there is exactly one result left on the stack
    if (s.empty())
        throw std::underflow_error("Stack underflow: not enough values on the stack");
    if (s.size() != 1)
        throw std::overflow_error("Stack overflow: too many values on the stack");
    return s.top();
}

std::vector<char> extract_variables(const std::string& formula) {
    std::set<char> vars; // Set to store unique variables
    for (char c : formula) {
        if (c >= 'A' && c <= 'Z') {
            vars.insert(c); // Add valid variable to the set
        } else if (c != '!' && c != '&' && c != '|' && c != '^' && c != '>' && c != '=') {
            // Throw an exception if an invalid character is encountered
            throw std::invalid_argument("Invalid character in formula");
        }
    }
    return std::vector<char>(vars.begin(), vars.end());
}

std::string substitute_values(const std::string& formula, const std::vector<char>& vars, const std::bitset<26>& values) {
    // Copy the original formula
    std::string substituted_formula = formula;
    // Replace each variable in the formula with its corresponding truth value
    for (size_t i = 0; i < vars.size(); ++i) {
        for (char& c : substituted_formula) {
            if (c == vars[i]) {
                // Replace variable with 1 (true) or 0 (false) based on the bitset
                c = values[i] ? '1' : '0';
            }
        }
    }
    return substituted_formula;
}

std::pair<std::string, std::vector<bool>> TruthTable::truth_table(const std::string& formula) {
    // Vector to store variables
    std::vector<char> vars;
    // Stores the formatted truth table and results
    std::pair<std::string, std::vector<bool>> table;
    try {
        // Extract variables from the formula
        vars = extract_variables(formula);
        // Create table header with variable names and result column
        table.first.append("| ");
        for (char var : vars)
            table.first.append(std::string(1, var) + " | ");
        table.first.append("= |\n");
        // Add separator line
        for (size_t i = 0; i <= vars.size(); i++)
            table.first.append("|---");
        table.first.append("|\n");
        // Iterate through all possible 2^n truth value combinations
        // where n is the number of the variables
        for (int i = 0; i < (1 << vars.size()); i++) {
            // Represent the current combination of truth values as a bitset
            std::bitset<26> values(i);
            // |-----------------------------------------|
            // | i | Binary of i | values[0] | values[1] |
            // |---|-------------|-----------|-----------|
            // | 0 |     00      |     0     |     0     |
            // | 1 |     01      |     1     |     0     |
            // | 2 |     10      |     0     |     1     |
            // | 3 |     11      |     1     |     1     |
            // |-----------------------------------------|
            // Construct a row for the truth table
            table.first.append("| ");
            for (size_t j = 0; j < vars.size(); j++) {
                // Extract the truth value for each variable using the bitset
                std::string value(values[j] ? "1" : "0");
                // Append the truth value to the row
                table.first.append(value + " | ");
            }
            // Substitute the current truth values into the formula and evaluate it
            bool result = boolean_evaluation(substitute_values(formula, vars, values));
            // Store the evaluation result
            table.second.push_back(result);
            // Append the evaluation result to the row.
            std::string value(result ? "1" : "0");
            // End of row's construction
            table.first.append(value + " |\n");
        }
    } catch (const std::exception& e) {
        // Handle errors by clearing the table and printing an error message
        table.first.clear();
        table.second.clear();
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return table;
}
