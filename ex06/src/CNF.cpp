#include "CNF.hpp"

CNF::CNF(std::string& formula) :
    NNF(formula) {
    // std::cout << "==== Converted NNF tree ====" << std::endl;
    //     std::cout << "Formula: " << _nnf_rpn << std::endl;
    // std::cout << "Tree:" << std::endl;
    // print_ast(_root.get());
    // std::cout << "============================" << std::endl;
    _to_cnf(_root.get());
    _cnf_rpn.clear();
    _to_rpn(_root.get(), _cnf_rpn);
    // std::cout << "==== Converted CNF tree ====" << std::endl;
    // std::cout << "Formula: " << _cnf_rpn << std::endl;
    // std::cout << "Tree:" << std::endl;
    // print_ast(_root.get());
    // std::cout << "============================" << std::endl;
}

static void flatten_nested(Node* node) {
    if (node == nullptr || node->get_type() == OPERAND)
        return;
    flatten_nested(node->get_left().get());
    if (node->get_type() == BINARY && (node->get_left()->get_token() == node->get_token()
            || (node->get_right()->get_token() == node->get_token()
                && node->get_left()->get_token() == node->get_token()))) {
        std::unique_ptr<Node> new_right = std::make_unique<Node>(
            node->get_left()->get_token(),
            std::move(node->get_left()->get_right()),
            std::move(node->get_right())
        );
        std::unique_ptr<Node> new_left(std::move(node->get_left()->get_left()));
        node->set_right(std::move(new_right));
        node->set_left(std::move(new_left));
    }
    flatten_nested(node->get_right().get());
}

static void conjunction_over_disjunction(Node* node) {
    if (node == nullptr || node->get_type() == OPERAND)
        return;
    conjunction_over_disjunction(node->get_left().get());
    if (node->get_token() == "|") {
        if (node->get_right()->get_token() == "&" && node->get_left()->get_token() == "&") {
            std::unique_ptr<Node> a = std::move(node->get_left()->get_left());
            std::unique_ptr<Node> b = std::move(node->get_left()->get_right());
            std::unique_ptr<Node> c = std::move(node->get_right()->get_left());
            std::unique_ptr<Node> d = std::move(node->get_right()->get_right());
            node->set_token("&");
            node->set_left(std::make_unique<Node>( "&",
                std::make_unique<Node>("|", std::make_unique<Node>(a->get_token()), std::make_unique<Node>(c->get_token())), 
                std::make_unique<Node>("|", std::make_unique<Node>(a->get_token()), std::make_unique<Node>(d->get_token()))));
            node->set_right(std::make_unique<Node>("&",
                std::make_unique<Node>("|", std::make_unique<Node>(b->get_token()), std::make_unique<Node>(c->get_token())), 
                std::make_unique<Node>("|", std::make_unique<Node>(b->get_token()), std::make_unique<Node>(d->get_token()))));
        } else if (node->get_right()->get_token() == "&") {
            std::unique_ptr<Node> right_right = std::make_unique<Node>(*node->get_right()->get_right());
            std::unique_ptr<Node> left_right = std::make_unique<Node>(*node->get_right()->get_left());
            std::unique_ptr<Node> right_left = std::make_unique<Node>(node->get_left()->get_token());
            std::unique_ptr<Node> left_left = std::make_unique<Node>(node->get_left()->get_token());
            node->set_token("&");
            node->set_right(std::make_unique<Node>("|", std::move(right_left), std::move(right_right)));
            node->set_left(std::make_unique<Node>("|", std::move(left_left), std::move(left_right)));
            conjunction_over_disjunction(node->get_left().get());
        } else if (node->get_left()->get_token() == "&") { 
            std::unique_ptr<Node> right_right = std::make_unique<Node>(node->get_right()->get_token());
            std::unique_ptr<Node> left_right = std::make_unique<Node>(node->get_right()->get_token());
            std::unique_ptr<Node> right_left = std::make_unique<Node>(*node->get_left()->get_right());
            std::unique_ptr<Node> left_left = std::make_unique<Node>(*node->get_left()->get_left());
            node->set_token("&");
            node->set_right(std::make_unique<Node>("|", std::move(right_left), std::move(right_right)));
            node->set_left(std::make_unique<Node>("|", std::move(left_left), std::move(left_right)));
            conjunction_over_disjunction(node->get_right().get());
        }
    }
    conjunction_over_disjunction(node->get_right().get());
}

void CNF::_to_cnf(Node* root) {
    conjunction_over_disjunction(root);
    flatten_nested(root);
}

const std::string& CNF::get_cnf() const {
    return _cnf_rpn;
}
