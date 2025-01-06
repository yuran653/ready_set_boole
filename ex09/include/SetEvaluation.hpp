#ifndef SETEVALUATION_HPP
#define SETEVALUATION_HPP

#include <cstdint>
#include <set>
#include <stdexcept>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "NNF.hpp"

class SetEvaluation {
    private:
        const std::string _input_formula;
        const std::vector<std::set<int32_t>> _input_sets;
        std::string _eval_formula;
        std::unordered_map<char, std::set<int32_t>> _literal_set_map;
        std::unordered_set<int32_t> _universal_set;
        mutable std::stack<std::unique_ptr<std::set<int32_t>>> _stack_eval_set;

        SetEvaluation() = delete;
        SetEvaluation(const SetEvaluation& other) = delete;
        SetEvaluation(SetEvaluation&& other) = delete;

        SetEvaluation& operator=(const SetEvaluation& other) = delete;

        bool _is_formula_valid() const;
        void _create_map();
        void _create_universal_set();
        void _evaluate_sets() const;
        void _complement() const;
        void _intersection() const;
        void _union() const;

    public:
        SetEvaluation(const std::string& formula, const std::vector<std::set<int32_t>>& sets);
        ~SetEvaluation() = default;


        const std::string& get_input_formula() const;
        const std::set<int32_t>& get_eval_set() const;
};

#endif
