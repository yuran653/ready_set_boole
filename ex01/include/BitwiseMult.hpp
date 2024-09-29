#ifndef BITWISEMULT_HPP
#define BITWISEMULT_HPP

#include <iostream>
#include <stdexcept>

class BitwiseMult {
public:
    BitwiseMult() = delete;
    ~BitwiseMult() = delete;

    static int bitwiseMult(int a, int b);

    class InputError : public std::invalid_argument {
    public:
        explicit InputError(const std::string& message)
            : std::invalid_argument(message) {}
    };
};

#endif
