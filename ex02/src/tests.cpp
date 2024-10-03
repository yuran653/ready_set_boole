#include <cassert>
#include <iostream>
#include <vector>
#include "GrayCode.hpp"

// Function to test cases from exercise examples
void examples_cases() {
    assert(GrayCode::gray_code(0) == 0);
    assert(GrayCode::gray_code(1) == 1);
    assert(GrayCode::gray_code(2) == 3);
    assert(GrayCode::gray_code(3) == 2);
    assert(GrayCode::gray_code(4) == 6);
    assert(GrayCode::gray_code(5) == 7);
    assert(GrayCode::gray_code(6) == 5);
    assert(GrayCode::gray_code(7) == 4);
    assert(GrayCode::gray_code(8) == 12);
}

// Function to test the maximum 'uint32_t' value
void max_case() {
    uint32_t max_value = UINT32_MAX;
    assert(GrayCode::gray_code(max_value) == (max_value ^ (max_value >> 1)));
}

// Function to test 20 predefined values from an array in a loop
void defined_cases() {
    std::vector<uint32_t> predefined_values = {9, 10, 12, 14, 17, 23, 75, 100, 255,
        512, 789, 1023, 2048, 3000, 4095, 5000, 65535, 8192, 32768, 65535};
    std::vector<uint32_t> expected_gray_codes = {13, 15, 10, 9, 25, 28, 110, 86,
        128, 768, 671, 512, 3072, 3684, 2048, 6732, 32768, 12288, 49152, 32768};
    auto val_it = predefined_values.begin();
    auto gray_it = expected_gray_codes.begin();
    for (; val_it != predefined_values.end() && gray_it != expected_gray_codes.end();
        ++val_it, ++gray_it)
        assert(GrayCode::gray_code(*val_it) == *gray_it);
}

// Function to check successive numbers should differ by only one bit
void single_bit_change() {
    // Test a range of values from 1 to 999
    for (uint32_t i = 1; i < 1000; i++) {
        uint32_t gray1 = GrayCode::gray_code(i);
        uint32_t gray2 = GrayCode::gray_code(i - 1);
        uint32_t xor_result = gray1 ^ gray2;
        // Check if the XOR has exactly one bit set
        assert(xor_result && !(xor_result & (xor_result - 1)));
    }
}

// Function to test a large number of inputs in a loop in the range UINT32_MAX-1000 to UINT32_MAX-1
void stress_test() {
    for (uint32_t i = UINT32_MAX - 1000; i < UINT32_MAX; i++)
        // Ensure it works for these values without crashing
        GrayCode::gray_code(i);
}

// Main function to run all test cases
int main() {
    examples_cases();          // Test example cases from exercise
    max_case();                // Test maximum uint32_t value
    defined_cases();           // Test predefined values from an array
    single_bit_change();       // Test successive numbers should differ by only one bit
    stress_test();             // Perform a stress test

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
