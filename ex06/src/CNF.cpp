#include "CNF.hpp"

std::string CNF::transform_to_cnf(const std::string& str) {
    std::string str_cnf = std::string();
    for (size_t i = 0; i < str.size(); ++i) {
        str_cnf.push_back(str.at(i));
        if (str.at(i) != '&' && str.at(i) != '|')
            continue;
        const ASTnode node = ASTnode::build_ast(str_cnf, str_cnf.size() - 1);
        const ASTnode& left = *(node.get_left());
        const ASTnode& right = *(node.get_right());
        if (node.get_token().back() == '&' && left.get_token().back() == '&') {
            const std::string r_child = right.get_token();
            str_cnf = str_cnf.substr(0, str_cnf.size() - r_child.size() - 2);
            str_cnf += r_child + std::string("&&");
        } else if (node.get_token().back() == '|' && right.get_token().back() == '&') {
            const std::string lhs = left.get_token();
            const std::string l_child = left.get_left()->get_token();
            const std::string r_child = right.get_right()->get_token();
            str_cnf = str_cnf.substr(0, str_cnf.size() - r_child.size() - 2);
            str_cnf += "|" + lhs + r_child + "|" + l_child + "&";
        } else if (node.get_token().back() == '|' && left.get_token().back() == '&') {
            const std::string lhs = left.get_token();
            const std::string l_child = left.get_left()->get_token();
            const std::string r_child = right.get_right()->get_token();
            str_cnf = str_cnf.substr(0, str_cnf.size() + lhs.size() + l_child.size() + r_child.size() - 2);
            str_cnf += lhs + l_child + "|" + lhs + r_child + "|" + l_child + "&";
        }
    }   
    return str_cnf;
}

bool CNF::is_valid(const std::string& str) noexcept {
    bool and_zone = true;
    for (auto i = str.rbegin(); i != str.rend(); i++) {
        if (*i == '&' && !and_zone) return false;
        if (*i == '&' && and_zone) continue;
        if (*i != '&') and_zone = false;
    }
    return true;
}

std::string CNF::toCNF(const std::string& formula) {
    std::string str = NNF::toNNF(formula);
    while (!is_valid(str))
        str = transform_to_cnf(str);
    return str;
}