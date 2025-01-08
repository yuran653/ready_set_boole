#include "TruthTable.hpp"

bool boolean_evaluation(const std::string& rpn) {
    std::stack<bool> s;
    bool a, b;
    for (char c : rpn) {
        if (c == '0') {
            s.push(false);
        } else if (c == '1') {
            s.push(true);
        } else {
            if (c == '!' && rpn.size() > 1) {
                a = s.top(); s.pop();
            } else if (s.size() < 2) {
                    throw std::underflow_error("Stack underflow: not enough values on the stack");
            } else {
                b = s.top(); s.pop();
                a = s.top(); s.pop();
            }
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
                    s.push(a != b);
                    break;
                case '>':
                    s.push(!a || b);
                    break;
                case '=':
                    s.push(a == b);
                    break;
                default:
                    throw std::invalid_argument("Invalid character in formula");
            }
        }
    }
    if (s.empty())
        throw std::underflow_error("Stack underflow: not enough values on the stack");
    if (s.size() != 1)
        throw std::overflow_error("Stack overflow: too many values on the stack");
    return s.top();
}

std::vector<char> extract_variables(const std::string& formula) {
    std::set<char> vars;
    for (char c : formula) {
        if (c >= 'A' && c <= 'Z')
            vars.insert(c);
        else if (c != '!' && c != '&' && c != '|' && c != '^' && c != '>' && c != '=')
            throw std::invalid_argument("Invalid character in formula");
    }
    return std::vector<char>(vars.begin(), vars.end());
}

std::string substitute_values(const std::string& formula, const std::vector<char>& vars, const std::bitset<26>& values) {
    std::string substituted_formula = formula;
    for (size_t i = 0; i < vars.size(); ++i) {
        for (char& c : substituted_formula) {
            if (c == vars[i])
                c = values[i] ? '1' : '0';
        }
    }
    return substituted_formula;
}

std::pair<std::string, std::vector<bool>> TruthTable::truth_table(const std::string& formula) {

    std::vector<char> vars;
    std::pair<std::string, std::vector<bool>> table;
    try {
        vars = extract_variables(formula);
        table.first.append("| ");
        for (char var : vars)
            table.first.append(std::string(1, var) + " | ");
        table.first.append("= |\n");
        for (size_t i = 0; i <= vars.size(); i++)
            table.first.append("|---");
        table.first.append("|\n");
        for (int i = 0; i < (1 << vars.size()); i++) {
            std::bitset<26> values(i);
            table.first.append("| ");
            for (size_t j = 0; j < vars.size(); j++) {
                std::string value(values[j] ? "1" : "0");
                table.first.append(value + " | ");
            }
            table.second.push_back(boolean_evaluation(substitute_values(formula, vars, values)) ? true : false);
            std::string value(table.second.back() ? "1" : "0");
            table.first.append(value + " |\n");
        }
    } catch (const std::exception& e) {
        table.first.clear();
        table.second.clear();
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return table;
}
