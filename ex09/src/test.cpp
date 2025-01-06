#include <iostream>
#include "SetEvaluation.hpp"

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"
#define OK "\xE2\x9C\x85"
#define KO "\xE2\x9D\x8C"

static void print_set(const std::set<int32_t>& set) {
    std::cout << "[";
    for (const auto& element : set) {
        if (element != *(set.rbegin()))
            std::cout << element << ", ";
        else
            std::cout << element;
    }
    std::cout << "]" << std::endl;
}

int main() {
    std::vector<std::tuple<std::string, std::vector<std::set<int32_t>>, std::set<int32_t>>> sets = {
        {"AB&", 
            {
                {0, 1, 2},
                {0, 3, 4},
            }, 
            {0}
        },
        {"AB|", 
            {
                {0, 1, 2},
                {3, 4, 5},
            }, 
            {0, 1, 2, 3, 4, 5}
        },
        {"A!", 
            {
                {0, 1, 2},
            }, 
            {} // Empty subset
        },
        {} // Empty set
    };

    for (auto it = sets.begin(); it != sets.end(); ++it) {
        try {
            SetEvaluation se(std::get<0>(*it), std::get<1>(*it));
            std::cout << "Formula: " << std::get<0>(*it) << std::endl;
            std::cout << "Sets to evaluate:" << std::endl;
            for (const auto& set : std::get<1>(*it))
                print_set(set);
            std::cout << "Evaluation set: ";
            print_set(se.get_eval_set());
            if (se.get_eval_set() == std::get<2>(*it))
                std::cout << GREEN << " OK " << RESET << OK;
            else
                std::cout << RED << " KO " << RESET << KO;
            std::cout << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: Formula: " << std::get<0>(*it) + ": "<< e.what() << std::endl;
        }
    }
    return 0;
}

