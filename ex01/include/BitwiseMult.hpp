#ifndef BITWISEMULT_HPP
#define BITWISEMULT_HPP

#include <cstdint>

class BitwiseMult {
    private:
        BitwiseMult() = delete;
        ~BitwiseMult() = delete;

        static uint32_t bitwise_add(const uint32_t a, const uint32_t b);
        
    public:
        static uint32_t bitwise_mult(const uint32_t a, const uint32_t b);

};

#endif
