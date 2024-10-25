#ifndef BOOLEANEVALUATION_HPP
#define BOOLEANEVALUATION_HPP

#include <iostream>
#include <stdexcept>
#include <stack>
#include <string>

class BooleanEvaluation {
    private:
        BooleanEvaluation() = delete;
        ~BooleanEvaluation() = delete;

    public:
        static bool booleanEvaluation(const std::string& rpn);
};

#endif
