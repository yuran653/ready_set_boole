#include "CNF.hpp"

CNF::CNF(std::string& formula) :
    NNF(formula) {
    // std::cout << "==== Converted NNF tree ====" << std::endl;
    //     std::cout << "Formula: " << _nnf_rpn << std::endl;
    // std::cout << "Tree:" << std::endl;
    // print_ast(_root.get());
    // std::cout << "============================" << std::endl;
    _to_cnf(_root.get());
    _cnf_rpn.clear();
    _to_rpn(_root.get(), _cnf_rpn);
    // std::cout << "==== Converted CNF tree ====" << std::endl;
    // std::cout << "Formula: " << _cnf_rpn << std::endl;
    // std::cout << "Tree:" << std::endl;
    // print_ast(_root.get());
    // std::cout << "============================" << std::endl;
}

bool CNF::_is_cnf(const Node* node) const {
    if (node == nullptr) {
        return true;
    } else if (node->get_type() == OPERAND) {
        return true;
    } else if (node->get_type() == BINARY) {
        if (node->get_right() == nullptr || node->get_left() == nullptr) {
            return false;
        } else if (node->get_right()->get_type() == OPERAND && node->get_left()->get_type() == OPERAND) {
            return true;
        } else if (node->get_token() == "|") {
            if (node->get_right()->get_token() == "&" || node->get_left()->get_token() == "&")
                return false;
            else
                return _is_cnf(node->get_right().get()) && _is_cnf(node->get_left().get());
        } else if (node->get_right()->get_type() == BINARY && node->get_left()->get_type() == BINARY
            && node->get_right()->get_token() == node->get_left()->get_token()) {
            return true;
        } else if (node->get_token() == "&") {
            if (node->get_right()->get_token() == "|" || node->get_left()->get_token() == "|")
                return _is_cnf(node->get_right().get()) && _is_cnf(node->get_left().get());
            else
                return false;
        } else {
            return false;
        }
    }
    return false;
}

void CNF::_to_cnf(Node* root) {
    if (_is_cnf(root)) {
        std::cout << "---> no conversion <---" << std::endl;
        print_ast(root);
        return;
    }
    // print_ast(root);
    // if (_is_cnf(root) == false)
    //     throw std::logic_error("Wrong conversion to CNF: formula \'" + _formula + "\'");
    std::cout << "!!!!! KO !!!!!!" << std::endl;
}

const std::string& CNF::get_cnf() const {
    return _cnf_rpn;
}
