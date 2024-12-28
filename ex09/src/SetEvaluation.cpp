#include "SetEvaluation.hpp"

SetEvaluation::SetEvaluation(const std::string& formula, const std::vector<std::set<int32_t>>& sets) :
    _input_formula(formula), _input_sets(sets) {
    if (_is_formula_valid() == false)
        throw std::invalid_argument("SetEvaluation: invalid input formula");
    if (_input_sets.empty())
        throw std::invalid_argument("SetEvaluation: input sets are empty/invalid");
}

bool SetEvaluation::_is_formula_valid() const {
    for (char c : _input_formula) {
        if (c != '!' && c != '&' && c!= '|' && c!= '^' && c!= '>' && c!= '=')
            return false;
        else if (c < 'A' || c > 'Z')
            return false;
    }
    return true;
}

void SetEvaluation::evaluate_sets() const {

}

const std::set<int32_t>& SetEvaluation::get_eval_set() const {
    return _eval_set;
}


