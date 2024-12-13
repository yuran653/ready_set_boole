






// #include "NNF.hpp"

// void apply_binary_operator(std::stack<std::string> &st, const char op) {
//     if (st.size() < 2)
//         throw std::runtime_error("Invalid formula: not enough operands for binary operator");
//     std::string right = st.top(); st.pop();
//     std::string left = st.top(); st.pop();
//     switch (op) {
//         case '&':
//         case '|':
//             st.push(left + right + op);
//             break;
//         case '>':
//             st.push(left + "!" + right + "|");
//             break;
//         case '=':
//             st.push(left + right + "&" + left + "!" + right + "!&|");
//             break;
//     }
// }

// void apply_negation(std::stack<std::string> &st) {
//     std::string top = st.top(); st.pop();
    
//     if (top.back() == '&' || top.back() == '|') {
//         char op = top.back();
//         std::string right = top.substr(top.size() - 2, 1);
//         std::string left = top.substr(0, top.size() - 2);
//         if (op == '&') {
//             st.push(left + "!" + right + "!|");
//         } else if (op == '|') {
//             st.push(left + "!" + right + "!&");
//         }
//     } else {
//         st.push(top + "!");
//     }
// }

// std::string NNF::toNNF(const std::string &formula) {
//     std::stack<std::string> st;
//     for (char token : formula) {
//         token = std::toupper(token);
//         switch (token) {
//             case 'A' ... 'Z':
//                 st.push(std::string(1, token));
//                 break;
//             case '&':
//             case '|':
//             case '>':
//             case '=':
//                 apply_binary_operator(st, token);
//                 break;
//             case '!':
//                 apply_negation(st);
//                 break;
//             default:
//                 throw std::runtime_error(std::string("Invalid formula: unsupported character '") + token + "'");
//         }
//     }
//     if (st.size() != 1)
//         throw std::runtime_error("Invalid formula: incorrect stack size after processing");
//     size_t n;
//     while ((n = st.top().find("!!")) != std::string::npos) {
//         st.top().erase(n, 2);
//     }
//     return st.top();
// }
