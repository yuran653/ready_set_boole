#ifndef SETEVALUATION_HPP
#define SETEVALUATION_HPP

#include <cstdint>
#include <set>
#include <stdexcept>
#include <stack>
#include <string>
#include <vector>

class SetEvaluation {
    private:
        const std::string _input_formula;
        const std::vector<std::set<int32_t>> _input_sets;
        std::stack<std::set<int32_t>> _stack_evq
        std::set<int32_t> _eval_set;

        SetEvaluation() = delete;
        SetEvaluation(const SetEvaluation& other) = delete;
        SetEvaluation(SetEvaluation&& other) = delete;

        SetEvaluation& operator=(const SetEvaluation& other) = delete;

        bool _is_formula_valid() const;

    public:
        SetEvaluation(const std::string& formula, const std::vector<std::set<int32_t>>& sets);
        ~SetEvaluation() = default;

        void evaluate_sets() const;

        const std::set<int32_t>& get_eval_set() const;
};

#endif
