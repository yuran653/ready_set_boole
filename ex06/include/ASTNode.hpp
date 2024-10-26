#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <memory>
#include <string>

class ASTnode {
    private:
        std::unique_ptr<ASTnode> _left = nullptr;
        std::unique_ptr<ASTnode> _right = nullptr;
        std::string _token = "";

        ASTnode() = delete;

        ASTnode& operator=(const ASTnode& other) = delete;

    public:
        ASTnode(const std::string& token,
            std::unique_ptr<ASTnode> left, std::unique_ptr<ASTnode> right);
        ASTnode(const ASTnode& other);
        ~ASTnode() = default;

        static ASTnode build_ast(const std::string& token, const ssize_t i);
        void print_ast(int depth) const;
};

#endif
