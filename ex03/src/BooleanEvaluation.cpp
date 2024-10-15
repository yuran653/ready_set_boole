#include "BooleanEvaluation.hpp"

bool BooleanEvaluation::booleanEvaluation(const std::string& rpn) {
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
                    throw std::underflow_error("Stack underflow: not enough values on the stack1");
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
        throw std::underflow_error("Stack underflow: not enough values on the stack2");
    if (s.size() != 1)
        throw std::overflow_error("Stack overflow: too many values on the stack");
    return s.top();
}
