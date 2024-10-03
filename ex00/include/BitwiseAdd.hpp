#ifndef BITWISEADD_HPP
#define BITWISEADD_HPP

#include <cstdint>

class BitwiseAdd {
    private:
        BitwiseAdd() = delete;
        ~BitwiseAdd() = delete;

    public:
        static uint32_t bitwise_add(const uint32_t a, const uint32_t b);
};

#endif
