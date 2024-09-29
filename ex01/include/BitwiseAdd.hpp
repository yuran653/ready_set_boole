#ifndef BITWISEADD_HPP
#define BITWISEADD_HPP

#include <iostream>
#include <stdexcept>

class BitwiseAdd {
public:
    BitwiseAdd() = delete;
    ~BitwiseAdd() = delete;

    static int bitwiseAdd(int a, int b);

    class InputError : public std::invalid_argument {
    public:
        explicit InputError(const std::string& message)
            : std::invalid_argument(message) {}
    };
};

#endif
