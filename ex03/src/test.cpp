#include <iostream>
#include "BooleanEvaluation.hpp"

void correctValues(const std::string& rpn, bool value) {
    std::cout << std::boolalpha;
    bool result = BooleanEvaluation::booleanEvaluation(rpn);
    std::cout << rpn << " -> " << result << ", Expected: " << value << " -> ";
    if (result == value)
        std::cout << "OK";
    else
        std::cout << "KO";
    std::cout << std::endl;
}

int main() {
    try {
        std::cout << "Correct Execution Tests:\n";
        correctValues("10&", false);
        correctValues("10|", true);
        correctValues("11>", true);
        correctValues("10=", false);
        correctValues("1011||=", true);
        correctValues("10&1&", false);
        correctValues("10|1|", true);
        correctValues("11&0&", false);
        correctValues("11|0|", true);
        correctValues("11&", true);
        correctValues("11^", false);
        correctValues("10^", true);
        correctValues("10&1=", false);
        correctValues("01=", false);
        correctValues("00=", true);
        correctValues("11^0^", false);
        correctValues("01^", true);
        correctValues("0!", true);
        correctValues("1!", false);
        correctValues("10|1|!", false);
        correctValues("10!1||", true);
        correctValues("11|0!|", true);
        correctValues("11|!0|", false);
        correctValues("11&!0&!", true);
        correctValues("01>", true);
        correctValues("10!1&=", true);
        correctValues("10!1|=", true);
        correctValues("11|1!=", false);
        correctValues("10&1^", true);
        correctValues("11^!0^", true);

        // Exception Tests
        std::cout << "\nException Tests:\n";
        
        // StackUnderflow
        try {
            std::cout << BooleanEvaluation::booleanEvaluation("!") << std::endl;   // Underflow with '!'
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

        try {
            std::cout << BooleanEvaluation::booleanEvaluation("0&!") << std::endl; // Underflow with '&'
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

        // StackOverflow
        try {
            std::cout << BooleanEvaluation::booleanEvaluation("01") << std::endl;  // Overflow: no operator
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

        try {
            std::cout << BooleanEvaluation::booleanEvaluation("101|1&!") << std::endl; // Overflow: missing operators
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

        // InvalidCharacter
        try {
            std::cout << BooleanEvaluation::booleanEvaluation("10X&") << std::endl; // Invalid character 'X'
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

        try {
            std::cout << BooleanEvaluation::booleanEvaluation("10%&") << std::endl; // Invalid character '%'
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
    }

    return 0;
}
