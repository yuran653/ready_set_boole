#include "CNF.hpp"

CNF::CNF(std::string& formula) :
    NNF(formula) {
    std::cout << "==== Converted NNF tree ====" << std::endl;
    print_ast(_root.get());
    std::cout << "============================" << std::endl;
    _to_cnf(_root.get());
    // std::cout << "==== Converted CNF tree ====" << std::endl;
    // print_ast(_root.get());
    // std::cout << "============================" << std::endl;
    _cnf_rpn.clear();
    _to_rpn(_root.get(), _cnf_rpn);
}

static bool is_literal(const Node* node) {
    if (node == nullptr)
        return false;
    std::cout << "is_literal: " << node->get_token() << std::endl;
    std::cout << "TYPE [" << node->get_type() << "]" << std::endl;
    if (node->get_type() == OPERAND) {
        std::cout << "OPERAND" << std::endl;
        std::cout << "LEFT [" << &node->get_left() << "]" << std::endl;
        std::cout << ((node->get_left() == nullptr) ? "nullptr" : "not nullptr") << std::endl;
        std::cout << "RIGHT [" << &node->get_right() << "]" << std::endl;
        std::cout << ((node->get_right() == nullptr) ? "nullptr" : "not nullptr") << std::endl;
        bool value = node->get_left() == nullptr && node->get_right() == nullptr;
        std::cout << "VALUE [" << value << "]" << std::endl;
        std::cout << "READY TO RETURN" << std::endl;
        return value;
        // return node->get_left() == nullptr && node->get_right() == nullptr;
    }
    if (node->get_type() == UNARY)
        return node->get_left() && node->get_left()->get_type() == OPERAND;
    return false;
}

static void parse_tree(const Node* node) {
    if (node == nullptr)
        return;
    if (node->get_token() == '&') {
        if (node->get_left() == nullptr || node->get_right() == nullptr)
            throw std::logic_error("Invalid CNF");
        if (node->get_left()->get_token() == '&' || node->get_right()->get_token() == '&')
            throw std::logic_error("Invalid CNF");
    } else if (node->get_token() == '|') {
        if (node->get_left() == nullptr || node->get_right() == nullptr
            || node->get_left()->get_token() == '&' || node->get_right()->get_token() == '&')
            throw std::logic_error("Invalid CNF");
        if (is_literal(node->get_left().get()) == false || is_literal(node->get_right().get()) == false)
            throw std::logic_error("Invalid CNF");
    } else {
        if (is_literal(node) == false)
            throw std::logic_error("Invalid CNF");
    }
    parse_tree(node->get_left().get());
    parse_tree(node->get_right().get());
}

bool CNF::_is_cnf(const Node* node) const {
    try {
        parse_tree(node);
    } catch (const std::exception& e) {
        return false;
    }
    return true;
}

static void conjunction_over_disjunction(Node* root) {
    if (root == nullptr)
        return;
    std::stack<Node*> stack;
    stack.push(root);
    try {
    while (!stack.empty()) {
        Node* node = stack.top();
        stack.pop();
        if (node->get_token() == '|') {
            std::unique_ptr<Node> saved_tree = std::make_unique<Node>(node->get_token(),
                std::move(node->get_left()), std::move(node->get_right()));
            bool value = is_literal(node->get_left().get());
            std::cout << "IS LITERAL [" << value << "]" << std::endl;
            if (value) {
            // if (is_literal(node->get_left().get())) {// && node->get_right()->get_token() == '&') {
                std::cout << "WE ARE INSIDE" << std::endl;
                if (node->get_right()->get_token() == '&') {
                node->set_token('&');
                node->set_left(std::make_unique<Node>(('|'),
                    std::make_unique<Node>(*saved_tree->get_left()),
                    std::move(saved_tree->get_right()->get_left())));
                node->set_right(std::make_unique<Node>(('|'),
                    std::make_unique<Node>(*saved_tree->get_left()),
                    std::move(saved_tree->get_right()->get_right())));}
            } else if (node->get_left()->get_token() == '&' && is_literal(node->get_right().get())) {
                node->set_token('&');
                node->set_left(std::make_unique<Node>(('|'),
                    std::move(saved_tree->get_left()->get_left()),
                    std::make_unique<Node>(*saved_tree->get_right())));
                node->set_right(std::make_unique<Node>(('|'),
                    std::move(saved_tree->get_left()->get_right()),
                    std::make_unique<Node>(*saved_tree->get_right())));
            } else if (node->get_left()->get_token() == '&' && node->get_right()->get_token() == '&') {
                std::unique_ptr<Node> a = std::move(saved_tree->get_left()->get_left());
                std::unique_ptr<Node> b = std::move(saved_tree->get_left()->get_right());
                std::unique_ptr<Node> c = std::move(saved_tree->get_right()->get_left());
                std::unique_ptr<Node> d = std::move(saved_tree->get_right()->get_right());
                node->set_token('&');
                node->set_left(std::make_unique<Node>('&',
                    std::make_unique<Node>('|', std::make_unique<Node>(*a), std::make_unique<Node>(*c)),
                    std::make_unique<Node>('|', std::make_unique<Node>(*a), std::make_unique<Node>(*d))));
                node->set_right(std::make_unique<Node>('&',
                    std::make_unique<Node>('|', std::make_unique<Node>(*b), std::make_unique<Node>(*c)),
                    std::make_unique<Node>('|', std::make_unique<Node>(*b), std::make_unique<Node>(*d))));
            }
        }
        if (node->get_right() != nullptr)
            stack.push(node->get_right().get());
        if (node->get_left() != nullptr)
            stack.push(node->get_left().get());
    }
    } catch (const std::exception& e) {
        std::cerr << "WTF: " << e.what() << std::endl;
    }
}

// static void conjunction_over_disjunction(Node* node) {
//     if (node == nullptr)
//         return;
//     if (node->get_token() == '|') {
//         if (is_literal(node->get_left().get()) && node->get_right()->get_token() == '&') {

//         } else if () {

//         } else if () {

//         }
//     }
//     conjunction_over_disjunction(node->get_left().get());
//     conjunction_over_disjunction(node->get_right().get());
// }

void CNF::_to_cnf(Node* root) {
    if (_is_cnf(root))
        return;
    conjunction_over_disjunction(root);
    std::cout << "== conjunction_over_disjunction ==" << std::endl;
    print_ast(root);
    std::cout << "==================================" << std::endl;
    if (_is_cnf(root) == false)
        throw std::logic_error("Wrong conversion to CNF");
}

const std::string& CNF::get_cnf() const {
    return _cnf_rpn;
}
