#ifndef AST_HPP
#define AST_HPP

#include <stdexcept>
#include <memory>
#include <string>

class ASTnode {
    private:
        std::unique_ptr<ASTnode> _left;
        std::unique_ptr<ASTnode> _right;
        std::string _token;

        ASTnode(const ASTnode& other) = delete;

        ASTnode& operator=(ASTnode& other) = delete;
        ASTnode& operator=(ASTnode&& other) = delete;

    public:
        ASTnode();
        ASTnode(ASTnode&& other) noexcept;
        ~ASTnode() = default;

        static ASTnode build_ast(const std::string& token, const ssize_t i);
        const std::unique_ptr<ASTnode>& get_left() const;
        const std::unique_ptr<ASTnode>& get_right() const;
        const std::string& get_token() const;
};

#endif
