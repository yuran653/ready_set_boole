#include "PowerSet.hpp"

PowerSet::PowerSet(const std::set<int32_t>& set) :
    _original_set(set), _subsets_amount(1 << _original_set.size()) {
    if (_original_set.empty())
        throw std::invalid_argument("PowerSet: empty input");
    if (_original_set.size() > 10)
        throw std::overflow_error("PowerSet: input set too large for powerset computation");
    _create_powerset();
    if (int32_t(_powerset.size()) != _subsets_amount)
        throw std::runtime_error("PowerSet: failed to create powerset");
}

void PowerSet::_create_powerset() {
    // Calculate the size of the input set (_original_set)
    int32_t n = _original_set.size();
    // Calculate the total number of subsets in the powerset (2^n)
    // This is derived from the fact that for each element, there are two choices:
    // include or exclude.
    int32_t subsets_amount = 1 << n;
    // Iterate through all possible subset representations (0 to 2^n - 1)
    for (int32_t i = 0; i < subsets_amount; ++i) {
        // Initialize an empty set to represent the current subset
        std::set<int32_t> subset;
        // Index to track the position of elements in the original set
        int32_t idx = 0;
        // Iterate over all elements in the original set
        for (std::set<int32_t>::iterator it = _original_set.begin(); it != _original_set.end(); ++it, ++idx) {
            // Check if the current bit (1 << idx) is set in the binary representation of 'i'
            // If the bit is set, include the corresponding element in the current subset
            if (i & (1 << idx)) {
                // Insert the element into the subset
                if (!subset.insert(*it).second) {
                    // Throw an error if there's any unexpected duplicate
                    throw std::runtime_error("PowerSet: duplicated value in subset");
                }
            }
        }
        // Add the generated subset to the powerset
        if (!_powerset.insert(subset).second) {
            // Throw an error if there are duplicate subsets
            throw std::runtime_error("PowerSet: duplicated subset");
        }
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
