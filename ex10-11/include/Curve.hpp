#ifndef CURVE_HPP
#define CURVE_HPP

#include <cstdint>
#include <utility>

class Curve {
    private:
        Curve() = delete;
        ~Curve() = delete;

    public:
        static double map(uint16_t x, uint16_t y);
        static std::pair<uint16_t, uint16_t> inverse_map(double z);
};

#endif
