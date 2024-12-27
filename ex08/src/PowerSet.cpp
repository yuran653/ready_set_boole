#include "PowerSet.hpp"

PowerSet::PowerSet(const std::set<int32_t>& set) :
    _original_set(set), _subsets_amount(1 << _original_set.size()) {
    if (_original_set.empty())
        throw std::invalid_argument("PowerSet: empty input");
    if (_original_set.size() > 10)
        throw std::overflow_error("PowerSet: nput set too large for powerset computation");
    _create_powerset();
    if (int32_t(_powerset.size()) != _subsets_amount)
        throw std::runtime_error("PowerSet: failed to create powerset");
}

void PowerSet::_create_powerset() {
    int32_t n = _original_set.size();
    int32_t subsets_amount = 1 << n;
    for (int32_t i = 0; i < subsets_amount; ++i) {
        std::set<int32_t> subset;
        int32_t idx = 0;
        for (std::set<int32_t>::iterator it = _original_set.begin(); it != _original_set.end(); ++it, ++idx) {
            if (i & (1 << idx)) {
                if (!subset.insert(*it).second) {
                    throw std::runtime_error("PowerSet: duplicated value in subset");
                }
            }
        }
        if (!_powerset.insert(subset).second)
            throw std::runtime_error("PowerSet: duplicated subset");
    }
}

void PowerSet::_print_set(const std::set<int32_t>& set) const {
    if (!set.empty()) {
        std::cout << "{";
        for (std::set<int32_t>::const_iterator it = set.begin(); it != set.end(); ++it) {
            if (it != set.begin())
                std::cout << ", ";
            std::cout << *it;
        }
        std::cout << "}" << std::endl;
    }
}

void PowerSet::print_original_set() const {
    std::cout << "Original set: ";
    _print_set(_original_set);
}

void PowerSet::print_powerset() const {
    std::cout << "Powerset: {" << std::endl;
    for (std::set<std::set<int32_t>>::const_iterator it = _powerset.begin(); it != _powerset.end(); ++it)
        _print_set(*it);
    std::cout << "}" << std::endl;
    std::cout << "Powerset size: " << _powerset.size() << std::endl;
}

const std::set<int32_t> PowerSet::get_original_set() const {
    return _original_set;
}

const std::set<std::set<int32_t>> PowerSet::get_powerset() const {
    return _powerset;
}
