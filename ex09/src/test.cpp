#include <iostream>
#include "SetEvaluation.hpp"

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
            {} // Empty set
        }
    };

    for (auto it = sets.begin(); it != sets.end(); ++it) {
        try {
            SetEvaluation se(std::get<0>(*it), std::get<1>(*it));
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}

