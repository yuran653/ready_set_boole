#include <cstdint>

class GrayCode {
    private:
        GrayCode() = delete;
        ~GrayCode() = delete;
    
    public:
        static uint32_t gray_code(const uint32_t n);
};
