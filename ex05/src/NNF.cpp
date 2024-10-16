#include "NNF.hpp"

void apply_binary_operator(std::stack<std::string> &st, const char op) {
    if (st.size() < 2)
        throw std::runtime_error("Invalid formula: not enough operands for binary operator");
    std::string right = st.top(); st.pop();
    std::string left = st.top(); st.pop();
    st.push(left + right + op);
}

void apply_negation(std::stack<std::string> &st) {
    if (st.empty())
        throw std::runtime_error("Invalid formula: missing operand for negation");
    std::string top = st.top(); st.pop();
    if (top.back() == '&' || top.back() == '|') {
        char op = top.back();
        std::string right = top.substr(top.size() - 2, 1);
        std::string left = top.substr(0, top.size() - 2);
        if (op == '&')
            st.push(left + "!" + right + "!|");
        else if (op == '|')
            st.push(left + "!" + right + "!&");
    } else {
        st.push(top + "!");
    }
}

std::string NNF::toNNF(const std::string &formula) {
    std::stack<std::string> st;
    for (char c : formula) {
        c = std::toupper(c);
        switch (c) {
            case 'A' ... 'Z':
                st.push(std::string(1, c));
                break;
            case '&':
            case '|':
                apply_binary_operator(st, c);
                break;
            case '!':
                apply_negation(st);
                break;
            default:
                throw std::runtime_error(std::string("Invalid formula: unsupported operator '") + c + "'");
        }
    }
    if (st.size() != 1)
        throw std::runtime_error("Invalid formula: incorrect stack size after processing");
    return st.top();
}
