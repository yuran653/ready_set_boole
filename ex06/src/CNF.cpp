#include "CNF.hpp"

CNF::CNF(std::string& formula) :
    NNF(formula) {
    // std::cout << "==== Converted NNF tree ====" << std::endl;
    // print_ast(_root.get());
    // std::cout << "============================" << std::endl;
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
    else if (node->get_type() == OPERAND)
        return node->get_left() == nullptr && node->get_right() == nullptr;
    else if (node->get_type() == UNARY)
        return node->get_left() && node->get_left()->get_type() == OPERAND;
    return false;
}

static void parse_tree(const Node* node) {
    if (node == nullptr)
        return;
    else if (node->get_type() == BINARY) {
        if (node->get_left() == nullptr || node->get_right() == nullptr)
            throw std::logic_error("Invalid CNF: case [&]: one of the leaves is \'nullptr\'");
        else if (node->get_left()->get_token() == '&' && node->get_right()->get_token() == '&')
            ;
        else if (node->get_token() == '|' && (node->get_left()->get_token() == '&' || node->get_right()->get_token() == '&'))
            throw std::logic_error("Invalid CNF: case [|]: one of the leaves is \'&\'");
        else if (node->get_token() == '|' && (is_literal(node->get_left().get()) == false && is_literal(node->get_right().get()) == false))
            throw std::logic_error("Invalid CNF: case [|]: one of the leaves is not a literal");
        else if ((node->get_left()->get_type() == BINARY && is_literal(node->get_right().get())))
            throw std::logic_error("Invalid CNF: cases [&]/[|]: has nested node");
        else if (node->get_left()->get_type() == BINARY && is_literal(node->get_left().get()))
            ;
    // else if (node->get_token() == '&') {
        // if (node->get_left() == nullptr || node->get_right() == nullptr)
        //     throw std::logic_error("Invalid CNF: case [&]: one of the leaves is \'nullptr\'");
        // if (node->get_left()->get_token() == '&' && node->get_right()->get_token() == '&')
        //     ;
        // else if ((node->get_left()->get_token() == '&' && is_literal(node->get_right().get())))
        //         throw std::logic_error("Invalid CNF: case [&]: node has nested conjunction");
        // else if (node->get_right()->get_token() == '&' && is_literal(node->get_left().get()))
        //         ;
    // } else if (node->get_token() == '|') {
        // if (node->get_left() == nullptr || node->get_right() == nullptr)
        //     throw std::logic_error("Invalid CNF: case [|]: one of the leaves is \'nullptr\'");
        // if (node->get_left()->get_token() == '&' || node->get_right()->get_token() == '&')
        //     throw std::logic_error("Invalid CNF: case [|]: one of the leaves is \'&\'");
        // if (node->get_left()->get_token() == '|' && is_literal(node->get_right().get()))
        //     throw std::logic_error("Invalid CNF: case [|]: node has nested disjunction");
        // else if (node->get_right()->get_token() == '|' && is_literal(node->get_left().get()))
        //     ;
        // else if (is_literal(node->get_left().get()) == false && is_literal(node->get_right().get()) == false)
        //     throw std::logic_error("Invalid CNF: case [|]: one of the leaves is not a literal");
    } else if (is_literal(node) == false) {
        throw std::logic_error("Invalid CNF: else case: node is not a literal");
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

bool CNF::_is_cnf_final(const Node* node) const {
    try {
        parse_tree(node);
    } catch (const std::exception& e) {
        std::cerr << "Error: \'_is_cnf\' false: " << e.what() << std::endl;
        return false;
    }
    return true;
}

static void conjunction_over_disjunction(Node* root) {
    if (root == nullptr)
        return;
    std::stack<Node*> stack;
    stack.push(root);
    while (!stack.empty()) {
        Node* node = stack.top();
        stack.pop();
        if (node->get_token() == '|' &&
            (is_literal(node->get_left().get()) == false || is_literal(node->get_right().get()) == false)) {
            if (is_literal(node->get_left().get()) && node->get_right()->get_token() == '&') {
                std::unique_ptr<Node> saved_tree = std::make_unique<Node>(node->get_token(),
                    std::move(node->get_left()), std::move(node->get_right()));
                node->set_token('&');
                node->set_left(std::make_unique<Node>(('|'),
                    std::make_unique<Node>(*saved_tree->get_left()),
                    std::move(saved_tree->get_right()->get_left())));
                node->set_right(std::make_unique<Node>(('|'),
                    std::make_unique<Node>(*saved_tree->get_left()),
                    std::move(saved_tree->get_right()->get_right())));
            } else if (node->get_left()->get_token() == '&' && is_literal(node->get_right().get())) {
                std::unique_ptr<Node> saved_tree = std::make_unique<Node>(node->get_token(),
                    std::move(node->get_left()), std::move(node->get_right()));
                node->set_token('&');
                node->set_left(std::make_unique<Node>(('|'),
                    std::move(saved_tree->get_left()->get_left()),
                    std::make_unique<Node>(*saved_tree->get_right())));
                node->set_right(std::make_unique<Node>(('|'),
                    std::move(saved_tree->get_left()->get_right()),
                    std::make_unique<Node>(*saved_tree->get_right())));
            } else if (node->get_left()->get_token() == '&' && node->get_right()->get_token() == '&') {
                std::unique_ptr<Node> saved_tree = std::make_unique<Node>(node->get_token(),
                    std::move(node->get_left()), std::move(node->get_right()));
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
}

static void flatten_nested(Node* root) {
    if (root == nullptr)
        return;
    flatten_nested(root->get_left().get());
    flatten_nested(root->get_right().get());
    if (root->get_type() == BINARY) {
        if ((root->get_left()->get_type() == BINARY && is_literal(root->get_right().get()))) {
            std::unique_ptr<Node> left = std::move(root->get_right());
            std::unique_ptr<Node> right = std::move(root->get_left());
            root->set_left(std::move(left));
            root->set_right(std::move(right));
        }
    }
}

void CNF::_to_cnf(Node* root) {
    if (_is_cnf(root) == false)
        conjunction_over_disjunction(root);
    if (_is_cnf(root) == false)
        flatten_nested(root);
    if (_is_cnf_final(root) == false)
        throw std::logic_error("Wrong conversion to CNF: formula \'" + _formula + "\'");
}

const std::string& CNF::get_cnf() const {
    return _cnf_rpn;
}
