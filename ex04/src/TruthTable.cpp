#include "TruthTable.hpp"

bool booleanEvaluation(const std::string& rpn) {
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

std::vector<char> extractVariables(const std::string& formula) {
    std::set<char> vars;
    for (char c : formula) {
        if (std::toupper(c) >= 'A' && std::toupper(c) <= 'Z')
            vars.insert(c);
        else if (c != '!' && c != '&' && c != '|' && c != '^' && c != '>' && c != '=')
            throw std::invalid_argument("Invalid character in formula");
    }
    return std::vector<char>(vars.begin(), vars.end());
}

std::string substituteValues(const std::string& formula, const std::vector<char>& vars, const std::bitset<26>& values) {
    std::string substituted_formula = formula;
    for (size_t i = 0; i < vars.size(); ++i) {
        for (char& c : substituted_formula) {
            if (c == vars[i])
                c = values[i] ? '1' : '0';
        }
    }
    return substituted_formula;
}

void TruthTable::truthTable(const std::string& formula) {

    std::vector<char> vars = extractVariables(formula);

    std::cout << "| ";
    for (char var : vars)
        std::cout << std::toupper(var) << " | ";
    std::cout << "= |" << std::endl;
    for (size_t i = 0; i <= vars.size(); i++)
        std::cout << "|---";
    std::cout << "|" << std::endl;

    for (size_t i = 0; i < 1 << vars.size(); i++) {
        std::bitset<26> values(i);

        std::cout << "| ";
        for (size_t j = 0; j < vars.size(); j++) {
            std::cout << values[j] << " | ";
        }

        std::cout << booleanEvaluation(substituteValues(formula, vars, values)) << " |" << std::endl;
    }
}
