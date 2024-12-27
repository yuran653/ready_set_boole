#include "PowerSet.hpp"

PowerSet::PowerSet(const std::set<int32_t>& set) :
    _original_set(set) {
    _create_powerset();
}

void PowerSet::_create_powerset() {
    int32_t n = _original_set.size();
    int32_t subsets_amount = 1 << n;
    for (int32_t i = 0; i < subsets_amount; ++i) {
        std::vector<int32_t> subset;
        int32_t idx = 0;
        for (std::set<int32_t>::iterator it = _original_set.begin(); it != _original_set.end(); ++it, ++idx) {
            if (i & (1 << idx))
                subset.push_back(*it);
        }
        _powerset.push_back(subset);
    }
}

typedef()
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
    for (std::vector<std::vector<int32_t>>::const_iterator it = _powerset.begin(); it != _powerset.end(); ++it)
        _print_set(*it);
    std::cout << "}" << std::endl;
    std::cout << "Powerset size: " << _powerset.size() << std::endl;
}

const std::set<int32_t> PowerSet::get_original_set() const {
    return _original_set;
}

const std::vector<std::vector<int32_t>> PowerSet::get_powerset() const {
    return _powerset;
}
