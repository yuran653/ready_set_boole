#include "NNF.hpp"
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
    _create_map();
    _create_universal_set();
    _evaluate_sets();
}

bool SetEvaluation::_is_formula_valid() const {
    for (const char& c : _input_formula) {
        if (!(std::isupper(c) || c == '!' || c == '&' || c == '|' || c == '^' || c == '>' || c == '='))
            return false;
    }
    return true;
}

void SetEvaluation::_create_map() {
    auto it = _input_sets.cbegin();
    for (const char& c : _input_formula) {
        if (std::isupper(c)) {
            if (it == _input_sets.cend()) {
                throw std::runtime_error("SetEvaluation: _create_map(): different amount of literals/sets");
            }
            _literal_set_map.insert(std::make_pair(c, *it));
            ++it;
        }
    }
    if (it != _input_sets.cend()) {
        throw std::runtime_error("SetEvaluation: _create_map(): different amount of literals/sets");
    }
}

void SetEvaluation::_create_universal_set() {
    for (const std::set<int32_t>& set : _input_sets) {
        for (int32_t element : set)
            _universal_set.insert(element);
    }
}

void SetEvaluation::_complement() const{
    if (_stack_eval_set.empty())
        throw std::runtime_error("SetEvaluation: _compliment(): stack is empty");
    std::unique_ptr<std::set<int32_t>> set = std::move(_stack_eval_set.top());
    _stack_eval_set.pop();
    std::unique_ptr<std::set<int32_t>> complement = std::make_unique<std::set<int32_t>>();
    for (int32_t element : *set) {
        if (_universal_set.find(element) == _universal_set.end())
            complement->insert(element);
    }
    _stack_eval_set.push(std::move(complement));
}

void SetEvaluation::_intersection() const {
    if (_stack_eval_set.size() < 2)
        throw std::runtime_error("SetEvaluation: _intersection(): not enough sets in the stack");
    std::unique_ptr<std::set<int32_t>> right = std::move(_stack_eval_set.top());
    _stack_eval_set.pop();
    std::unique_ptr<std::set<int32_t>> left = std::move(_stack_eval_set.top());
    _stack_eval_set.pop();
    std::unique_ptr<std::set<int32_t>> intersection = std::make_unique<std::set<int32_t>>();
    for (int32_t element : *left) {
        if (right->find(element) != right->end())
            intersection->insert(element);
    }
    _stack_eval_set.push(std::move(intersection));
}

void SetEvaluation::_union() const {
    if (_stack_eval_set.size() < 2)
        throw std::runtime_error("SetEvaluation: _union(): not enough sets in the stack");
    std::unique_ptr<std::set<int32_t>> right = std::move(_stack_eval_set.top());
    _stack_eval_set.pop();
    std::unique_ptr<std::set<int32_t>> left = std::move(_stack_eval_set.top());
    _stack_eval_set.pop();
    for (int32_t element : *left) {
        right->insert(element);
    }
    _stack_eval_set.push(std::move(right));
}

void SetEvaluation::_evaluate_sets() const {
    for (const char& c : _eval_formula) {
        if (std::isupper(c))
            _stack_eval_set.push(std::make_unique<std::set<int32_t>>(_literal_set_map.at(c)));
        else {
            switch (c) {
            case '!':
                if (_stack_eval_set.empty())
                    throw std::runtime_error("SetEvaluation: _evaluate_sets(): complement impossible - missing operand");
                _complement();
                break;
            case '&':
                _intersection();
                break;
            case '|':
                _union();
                break;
            default:
                throw std::runtime_error("SetEvaluation: _evaluate_sets(): invalid symbol in formula");
            }
        }
    }
    if (_stack_eval_set.size() != 1)
        throw std::runtime_error("SetEvaluation: _evaluate_sets(): different amount of literals/sets");
}

const std::string& SetEvaluation::get_input_formula() const {
    return _input_formula;
}

const std::set<int32_t>& SetEvaluation::get_eval_set() const {
    return *_stack_eval_set.top();
}
