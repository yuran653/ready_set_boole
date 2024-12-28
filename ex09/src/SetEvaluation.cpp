#include "SetEvaluation.hpp"

SetEvaluation::SetEvaluation(const std::string& formula, const std::vector<std::set<int32_t>>& sets) :
    _input_formula(formula), _input_sets(sets) {
    if (_is_formula_valid() == false)
        throw std::invalid_argument("SetEvaluation: invalid input formula");
    if (_input_sets.empty())
        throw std::invalid_argument("SetEvaluation: input sets are empty/invalid");
    try {
        std::string input_formula(_input_formula);
        NNF nnf(input_formula);
        _eval_formula = nnf.get_nnf();
    } catch (const std::exception& e) {
        throw std::runtime_error("SetEvaluation: NNF: " + std::string(e.what()));
    }
    _evaluate_sets();
}

bool SetEvaluation::_is_formula_valid() const {
    for (char c : _input_formula) {
        if (!(std::isupper(c) || c == '!' || c == '&' || c == '|' || c == '^' || c == '>' || c == '='))
            return false;
    }
    return true;
}

void SetEvaluation::_evaluate_sets() const {
    std::cout << "Formula to evaluate: " << _eval_formula << std::endl;
}

const std::set<int32_t>& SetEvaluation::get_eval_set() const {
    return _eval_set;
}


