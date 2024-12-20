#include "CNF.hpp"

CNF::CNF(std::string& formula) :
    NNF(formula) {
    // _to_cnf(_root.get());
    // std::cout << "==== Converted CNF tree ====" << std::endl;
    // print_ast(_root.get());
    // std::cout << "============================" << std::endl;
    _cnf_rpn.clear();
    _to_rpn(_root.get(), _cnf_rpn);
}

const std::string& CNF::get_cnf() const {
    return _cnf_rpn;
}
