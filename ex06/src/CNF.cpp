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
    _cnf_to_rpn(_root.get());
    // std::cout << "==== Converted CNF tree ====" << std::endl;
    // std::cout << "Formula: " << _cnf_rpn << std::endl;
    // std::cout << "Tree:" << std::endl;
    // print_ast(_root.get());
    // std::cout << "============================" << std::endl;
}

// static void cnf_to_rpn(const Node* node, ssize_t level, std::string& rpn) {
//     if (node == nullptr)
//         return;
//     if (level == 1) {
//         std::cout << node->get_token();
//         rpn.insert(0, node->get_token());
//     } else if (level > 1) {
//         cnf_to_rpn(node->get_right().get(), level - 1, rpn);
//         cnf_to_rpn(node->get_left().get(), level - 1, rpn);
//     }
// }

// static ssize_t get_depth(const Node* node) {
//     if (node == nullptr)
//         return 0;
//     return 1 + std::max(get_depth(node->get_left().get()), get_depth(node->get_right().get()));
// }

void CNF::_cnf_to_rpn(const Node* root) {
    // ssize_t depth = get_depth(root);
    // for (int i = 1; i <= depth; ++i)
    //     cnf_to_rpn(root, i, _cnf_rpn);
    // std::cout << std::endl;
    if (!root) {
        return;
    }

    // // Traverse the left subtree
    // if (root->get_left()) {
        // _cnf_to_rpn(root->get_left().get());
    // }
    // // Traverse the right subtree
    // if (root->get_right()) {
        _cnf_to_rpn(root->get_right().get());
    // }
        _cnf_to_rpn(root->get_left().get());


    // Append the current node's token to the RPN string
    _cnf_rpn += root->get_token();
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

// static void parse_tree(const Node* node) {
//     if (node == nullptr)
//         return;
//     else if (node->get_token() == "&") {
//         if (node->get_left() == nullptr || node->get_right() == nullptr) {
//             throw std::logic_error("Invalid CNF: case [&]: one of the leaves is \'nullptr\'");
//         } else if (node->get_left()->get_token() == "&" && node->get_right()->get_token() == "&") {
//             ;
//         } else if ((node->get_left()->get_token() == "&" && is_literal(node->get_right().get()))) {
//             if (node->get_left()->get_left()->get_token() == "&" || node->get_left()->get_right()->get_token() == "&" )
//                 throw std::logic_error("Invalid CNF: case [&]: node has nested disjunction");
//             throw std::logic_error("Invalid CNF: case [&]: node has nested conjunction");
//         } else if (node->get_right()->get_token() == "&" && is_literal(node->get_left().get())) {
//             if (node->get_right()->get_left()->get_token() == "&" || node->get_right()->get_right()->get_token() == "&" )
//                 throw std::logic_error("Invalid CNF: case [&]: node has nested disjunction");
//         }
//     } else if (node->get_token() == "|") {
//         if (node->get_left() == nullptr || node->get_right() == nullptr) {
//             throw std::logic_error("Invalid CNF: case [|]: one of the leaves is \'nullptr\'");
//         } else if (node->get_left()->get_token() == "&" || node->get_right()->get_token() == "&") {
//             throw std::logic_error("Invalid CNF: case [|]: one of the leaves is \'&\'");
//         } else if (node->get_left()->get_token() == "|" && node->get_right()->get_token() == "|") {
//             ;
//         } else if (node->get_left()->get_token() == "|" && is_literal(node->get_right().get())) {
//             if (node->get_left()->get_left()->get_token() == "|" || node->get_left()->get_right()->get_token() == "|")
//                 throw std::logic_error("Invalid CNF: case [|]: node has nested disjunction");
//         } else if (node->get_right()->get_token() == "|" && is_literal(node->get_left().get())) {
//             if (node->get_right()->get_left()->get_token() == "|" || node->get_right()->get_right()->get_token() == "|")
//                 throw std::logic_error("Invalid CNF: case [|]: node has nested disjunction");
//         } else if (is_literal(node->get_left().get()) == false && is_literal(node->get_right().get()) == false) {
//             throw std::logic_error("Invalid CNF: case [|]: one of the leaves is not a literal");
//         }
//     } else if (is_literal(node) == false) {
//         throw std::logic_error("Invalid CNF: else case: node is not a literal");
//     }
//     parse_tree(node->get_left().get());
//     parse_tree(node->get_right().get());
// }

// bool CNF::_is_cnf(const Node* node) const {
//     try {
//         parse_tree(node);
//     } catch (const std::exception& e) {
//         return false;
//     }
//     return true;
// }

// static void conjunction_over_disjunction(Node* root) {
//     if (root == nullptr)
//         return;
//     std::stack<Node*> stack;
//     stack.push(root);
//     while (!stack.empty()) {
//         Node* node = stack.top();
//         stack.pop();
//         if (node->get_token() == '|' &&
//             (is_literal(node->get_left().get()) == false || is_literal(node->get_right().get()) == false)) {
//             if (is_literal(node->get_left().get()) && node->get_right()->get_token() == '&') {
//                 std::unique_ptr<Node> saved_tree = std::make_unique<Node>(node->get_token(),
//                     std::move(node->get_left()), std::move(node->get_right()));
//                 node->set_token('&');
//                 node->set_left(std::make_unique<Node>(('|'),
//                     std::make_unique<Node>(*saved_tree->get_left()),
//                     std::move(saved_tree->get_right()->get_left())));
//                 node->set_right(std::make_unique<Node>(('|'),
//                     std::make_unique<Node>(*saved_tree->get_left()),
//                     std::move(saved_tree->get_right()->get_right())));
//             } else if (node->get_left()->get_token() == '&' && is_literal(node->get_right().get())) {
//                 std::unique_ptr<Node> saved_tree = std::make_unique<Node>(node->get_token(),
//                     std::move(node->get_left()), std::move(node->get_right()));
//                 node->set_token('&');
//                 node->set_left(std::make_unique<Node>(('|'),
//                     std::move(saved_tree->get_left()->get_left()),
//                     std::make_unique<Node>(*saved_tree->get_right())));
//                 node->set_right(std::make_unique<Node>(('|'),
//                     std::move(saved_tree->get_left()->get_right()),
//                     std::make_unique<Node>(*saved_tree->get_right())));
//             } else if (node->get_left()->get_token() == '&' && node->get_right()->get_token() == '&') {
//                 std::unique_ptr<Node> saved_tree = std::make_unique<Node>(node->get_token(),
//                     std::move(node->get_left()), std::move(node->get_right()));
//                 std::unique_ptr<Node> a = std::move(saved_tree->get_left()->get_left());
//                 std::unique_ptr<Node> b = std::move(saved_tree->get_left()->get_right());
//                 std::unique_ptr<Node> c = std::move(saved_tree->get_right()->get_left());
//                 std::unique_ptr<Node> d = std::move(saved_tree->get_right()->get_right());
//                 node->set_token('&');
//                 node->set_left(std::make_unique<Node>('&',
//                     std::make_unique<Node>('|', std::make_unique<Node>(*a), std::make_unique<Node>(*c)),
//                     std::make_unique<Node>('|', std::make_unique<Node>(*a), std::make_unique<Node>(*d))));
//                 node->set_right(std::make_unique<Node>('&',
//                     std::make_unique<Node>('|', std::make_unique<Node>(*b), std::make_unique<Node>(*c)),
//                     std::make_unique<Node>('|', std::make_unique<Node>(*b), std::make_unique<Node>(*d))));
//                 }
//         }
//         if (node->get_right() != nullptr)
//             stack.push(node->get_right().get());
//         if (node->get_left() != nullptr)
//             stack.push(node->get_left().get());
//     }
// }

static void conjunction_over_disjunction(Node* node) {
    if (node == nullptr)
        return;
    if (node->get_token() == "|" &&
        !(is_literal(node->get_left().get()) == true && is_literal(node->get_right().get()) == true)) {
            std::cout << "-> conjunction over disjunctiuon <-" << std::endl;
        if (is_literal(node->get_left().get()) && node->get_right()->get_token() == "&") {
            std::unique_ptr<Node> saved_tree = std::make_unique<Node>(node->get_token(),
                std::move(node->get_left()), std::move(node->get_right()));
            node->set_token("&");
            node->set_left(std::make_unique<Node>(("|"),
                std::make_unique<Node>(*saved_tree->get_left()),
                std::move(saved_tree->get_right()->get_left())));
            node->set_right(std::make_unique<Node>(("|"),
                std::make_unique<Node>(*saved_tree->get_left()),
                std::move(saved_tree->get_right()->get_right())));
        } else if (node->get_left()->get_token() == "&" && is_literal(node->get_right().get())) {
            std::unique_ptr<Node> saved_tree = std::make_unique<Node>(node->get_token(),
                std::move(node->get_left()), std::move(node->get_right()));
            node->set_token("&");
            node->set_left(std::make_unique<Node>(("|"),
                std::move(saved_tree->get_left()->get_left()),
                std::make_unique<Node>(*saved_tree->get_right())));
            node->set_right(std::make_unique<Node>(("|"),
                std::move(saved_tree->get_left()->get_right()),
                std::make_unique<Node>(*saved_tree->get_right())));
        } else if (node->get_left()->get_token() == "&" && node->get_right()->get_token() == "&") {
            std::unique_ptr<Node> saved_tree = std::make_unique<Node>(node->get_token(),
                std::move(node->get_left()), std::move(node->get_right()));
            std::unique_ptr<Node> a = std::move(saved_tree->get_left()->get_left());
            std::unique_ptr<Node> b = std::move(saved_tree->get_left()->get_right());
            std::unique_ptr<Node> c = std::move(saved_tree->get_right()->get_left());
            std::unique_ptr<Node> d = std::move(saved_tree->get_right()->get_right());
            node->set_token("&");
            node->set_left(std::make_unique<Node>("&",
                std::make_unique<Node>("|", std::make_unique<Node>(*a), std::make_unique<Node>(*c)),
                std::make_unique<Node>("|", std::make_unique<Node>(*a), std::make_unique<Node>(*d))));
            node->set_right(std::make_unique<Node>("&",
                std::make_unique<Node>("|", std::make_unique<Node>(*b), std::make_unique<Node>(*c)),
                std::make_unique<Node>("|", std::make_unique<Node>(*b), std::make_unique<Node>(*d))));
            }
    }
    conjunction_over_disjunction(node->get_left().get());
    conjunction_over_disjunction(node->get_right().get());
}

static void flatten_nested(Node* root) {
    if (root == nullptr)
        return;
    if (root->get_type() == BINARY && root->get_left() && root->get_right()
        && (root->get_left()->get_type() != BINARY || root->get_right()->get_type() != BINARY)) {
        std::cout << "---> flatten_nested <---" << std::endl;
        if (root->get_right() && root->get_left()->get_left() && root->get_left()->get_right()) {
            std::unique_ptr<Node> right_branch = std::make_unique<Node>(
                root->get_left()->get_token(),
                std::move(root->get_left()->get_right()),
                std::move(root->get_right())
            );
            std::unique_ptr<Node> left_branch = std::move(root->get_left()->get_left());
            root->set_right(std::move(right_branch));
            root->set_left(std::move(left_branch));
        }
    }
    flatten_nested(root->get_left().get());
    flatten_nested(root->get_right().get());
}

// static void flatten_nested(Node* root) {
//     if (root == nullptr)
//         return;
//     std::vector<std::unique_ptr<Node>> literals;
//     std::stack<Node*> stack;
//     stack.push(root);
//     char operator_token = root->get_token();
//     while (!stack.empty()) {
//         Node* node = stack.top();
//         stack.pop();
//         if (node->get_type() == BINARY && node->get_token() == operator_token) {
//             if (node->get_right())
//                 stack.push(node->get_right().get());
//             if (node->get_left())
//                 stack.push(node->get_left().get());
//         } else if (is_literal(node)) {
//             literals.push_back(std::make_unique<Node>(*node));
//         } else {
//             throw std::logic_error("Invalid formula: flatten_nested: invalid operator: ["
//                 + std::string(1, operator_token) + "]");
//         }
//     }
//     while (literals.size() > 1) {
//         std::unique_ptr<Node> left = std::move(literals.back());
//         literals.pop_back();
//         std::unique_ptr<Node> right = std::move(literals.back());
//         literals.pop_back();
//         std::unique_ptr<Node> combined = std::make_unique<Node>(operator_token, std::move(right), std::move(left));
//         literals.push_back(std::move(combined));
//     }
//     root->set_type(BINARY);
//     root->set_token(operator_token);
//     root->set_left(std::move(literals.front()->get_left()));
//     root->set_right(std::move(literals.front()->get_right()));
// }

static void parse_tree(Node* node) {
    if (node == nullptr)
        return;
    else if (node->get_token() == "&") {
        if (node->get_left() == nullptr || node->get_right() == nullptr) {
            throw std::logic_error("Invalid CNF: case [&]: one of the leaves is \'nullptr\'");
        } else if (node->get_left()->get_token() == "&" && node->get_right()->get_token() == "&") {
            ;
        } else if ((node->get_left()->get_token() == "&" && is_literal(node->get_right().get()))) {
            if (node->get_left()->get_left()->get_token() == "&" || node->get_left()->get_right()->get_token() == "&" )
                flatten_nested(node);
                // throw std::logic_error("Invalid CNF: case [&]: node has nested conjunction");
        } else if (node->get_right()->get_token() == "&" && is_literal(node->get_left().get())) {
            if (node->get_right()->get_left()->get_token() == "&" || node->get_right()->get_right()->get_token() == "&" )
                flatten_nested(node);
                // throw std::logic_error("Invalid CNF: case [&]: node has nested conjunction");
        }
    } else if (node->get_token() == "|") {
        if (node->get_left() == nullptr || node->get_right() == nullptr) {
            throw std::logic_error("Invalid CNF: case [|]: one of the leaves is \'nullptr\'");
        } else if (node->get_left()->get_token() == "&" || node->get_right()->get_token() == "&") {
            conjunction_over_disjunction(node);
            // throw std::logic_error("Invalid CNF: case [|]: one of the leaves is conjunction");
        } else if (node->get_left()->get_token() == "|" && node->get_right()->get_token() == "|") {
            ;
        } else if (node->get_left()->get_token() == "|" && is_literal(node->get_right().get())) {
            if (node->get_left()->get_left()->get_token() == "|" || node->get_left()->get_right()->get_token() == "|")
                flatten_nested(node);
                // throw std::logic_error("Invalid CNF: case [|]: node has nested disjunction");
        } else if (node->get_right()->get_token() == "|" && is_literal(node->get_left().get())) {
            if (node->get_right()->get_left()->get_token() == "|" || node->get_right()->get_right()->get_token() == "|")
                flatten_nested(node);
                // throw std::logic_error("Invalid CNF: case [|]: node has nested disjunction");
        } else if (is_literal(node->get_left().get()) == false && is_literal(node->get_right().get()) == false) {
            throw std::logic_error("Invalid CNF: case [|]: one of the leaves is not a literal");
        }
    } else if (is_literal(node) == false) {
        throw std::logic_error("Invalid CNF: else case: node is not a literal");
    }
    parse_tree(node->get_left().get());
    parse_tree(node->get_right().get());
}
bool CNF::_is_cnf(Node* node) const {
    try {
        parse_tree(node);
    } catch (const std::exception& e) {
        return false;
    }
    return true;
}

void CNF::_to_cnf(Node* root) {
    // if (_is_cnf(root)) {
    //     std::cout << "---> no conversion <---" << std::endl;
    //     return;
    // }
    // conjunction_over_disjunction(root);
    // // if (_is_cnf(root))
    // //     return;
    // flatten_nested(root);
    if (_is_cnf(root) == false)
        throw std::logic_error("Wrong conversion to CNF: formula \'" + _formula + "\'");
}

const std::string& CNF::get_cnf() const {
    return _cnf_rpn;
}
