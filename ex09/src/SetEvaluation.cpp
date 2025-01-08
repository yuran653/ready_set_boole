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

void SetEvaluation::_complement() const {
    // Check if the stack is empty (no operand available)
    if (_stack_eval_set.empty())
        throw std::runtime_error("SetEvaluation: _compliment(): stack is empty");
    // Extract the top set from the stack
    std::unique_ptr<std::set<int32_t>> set = std::move(_stack_eval_set.top());
    _stack_eval_set.pop();
    // Create a new set to store the complement
    std::unique_ptr<std::set<int32_t>> complement = std::make_unique<std::set<int32_t>>();
    // Iterate through the universal set and find elements not in the operand set
    for (int32_t element : _universal_set) {
        if (set->find(element) == set->end())
            complement->insert(element);
    }
    // Push the complement set back onto the stack
    _stack_eval_set.push(std::move(complement));
}

void SetEvaluation::_intersection() const {
    // Check if there are at least two sets on the stack
    if (_stack_eval_set.size() < 2)
        throw std::runtime_error("SetEvaluation: _intersection(): not enough sets in the stack");
    // Extract the top two sets from the stack
    std::unique_ptr<std::set<int32_t>> right = std::move(_stack_eval_set.top());
    _stack_eval_set.pop();
    std::unique_ptr<std::set<int32_t>> left = std::move(_stack_eval_set.top());
    _stack_eval_set.pop();
    // Create a new set to store the intersection
    std::unique_ptr<std::set<int32_t>> intersection = std::make_unique<std::set<int32_t>>();
    // Add elements present in both sets
    for (int32_t element : *left) {
        if (right->find(element) != right->end()) // Element exists in both sets
            intersection->insert(element);
    }
    // Push the intersection set back onto the stack
    _stack_eval_set.push(std::move(intersection));
}

void SetEvaluation::_union() const {
    // Check if there are at least two sets on the stack
    if (_stack_eval_set.size() < 2)
        throw std::runtime_error("SetEvaluation: _union(): not enough sets in the stack");
    // Extract the top two sets from the stack
    std::unique_ptr<std::set<int32_t>> right = std::move(_stack_eval_set.top());
    _stack_eval_set.pop();
    std::unique_ptr<std::set<int32_t>> left = std::move(_stack_eval_set.top());
    _stack_eval_set.pop();
    // Add all elements from the left set to the right set
    for (int32_t element : *left) {
        right->insert(element);
    }
    // Push the resulting union set back onto the stack
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
