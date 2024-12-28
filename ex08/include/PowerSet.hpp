#ifndef POWERSET_HPP
#define POWERSET_HPP

#include <iostream>
#include <set>

class PowerSet {
    private:
        const std::set<int32_t> _original_set;
        const int32_t _subsets_amount;
        std::set<std::set<int32_t>> _powerset;

        PowerSet() = delete;
        PowerSet(const PowerSet& other) = delete;
        PowerSet(PowerSet&& other) = delete;

        PowerSet& operator=(const PowerSet& other) = delete;

        void _create_powerset();
        void _print_set(const std::set<int32_t>& set) const;

    public:
        explicit PowerSet(const std::set<int32_t>& set);
        ~PowerSet() = default;

        void print_original_set() const;
        void print_powerset() const;
        const std::set<int32_t> get_original_set() const;
        const std::set<std::set<int32_t>> get_powerset() const;
};

#endif
