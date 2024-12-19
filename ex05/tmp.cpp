#include <iostream>
#include <string>
#include <memory>

int main () {
    std::string str("Hello");
    std::unique_ptr<std::string> str1 = std::make_unique<std::string>(str);
    std::unique_ptr<std::string> str2 = std::make_unique<std::string>(str);
    str1->append(" World");
    str2->append(" WTF");
    std::cout << str << "\t\t->\t" << &str << std::endl;
    std::cout << *str1 << "\t->\t" << &str1 << std::endl;
    std::cout << *str2 << "\t->\t" << &str2 << std::endl;
    return 0;
}