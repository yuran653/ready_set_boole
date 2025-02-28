#include "NNF.hpp"

NNF::NNF(std::string& formula) :
    _formula(_remove_redundant_negation_str(formula)),
    _root(_build_ast()) {
    if (_root == nullptr)
        throw std::runtime_error("Invalid formula / Unable to build AST");
    // std::cout << "======= Original tree ======" << std::endl;
    // std::cout << "Formula: " << _formula << std::endl;
    // std::cout << "Tree:" << std::endl;
    // print_ast(_root.get());
    // std::cout << "============================" << std::endl;
    _to_nnf(_root.get());
    _nnf_rpn.clear();
    _to_rpn(_root.get(), _nnf_rpn);
    // std::cout << "==== Converted NNF tree ====" << std::endl;
    // std::cout << "Formula: " << _nnf_rpn << std::endl;
    // std::cout << "Tree:" << std::endl;
    // print_ast(_root.get());
    // std::cout << "============================" << std::endl;
}

const std::string& NNF::_remove_redundant_negation_str(std::string& input) {
    size_t position = input.find("!!");
    while (position != std::string::npos && position != 0) {
        input.erase(position, 2);
        position = input.find("!!");
    }
    return input;
}

static std::unique_ptr<Node> build_ast(const std::string& formula, ssize_t& idx) {
    if (idx < 0)
        return nullptr;
    char token = formula[idx--];
    if (token >= 'A' && token <= 'Z') {
        return std::make_unique<Node>(std::string(1, token));
    } else if (token == '!') {
        std::unique_ptr<Node> left = build_ast(formula, idx);
        return std::make_unique<Node>(std::string(1, token), std::move(left));
    }
    else if (token == '&' || token == '|' || token == '>' || token == '=' || token == '^') {
        std::unique_ptr<Node> right = build_ast(formula, idx);
        std::unique_ptr<Node> left = build_ast(formula, idx);
        return std::make_unique<Node>(std::string(1, token), std::move(left), std::move(right));
    } else {
        throw std::invalid_argument("Invalid character in formula");
    }
    return nullptr;
}

std::unique_ptr<Node> NNF::_build_ast() {
    ssize_t idx = _formula.size() - 1;
    std::unique_ptr<Node> root(nullptr);
    try {
        root = build_ast(_formula, idx);
        if (idx != -1)
            throw std::invalid_argument("Incorrect formula");
    } catch (const std::exception& e) {
        std::cerr << "Error: build_ast: " << e.what() << std::endl;
        return nullptr;
    }
    return root;
}

void NNF::_to_rpn(const Node* root, std::string& formula) {
    if (root->get_type() == OPERAND) {
        formula += root->get_token();
        return;
    } else if (root->get_type() == BINARY) {
        _to_rpn(root->get_left().get(), formula);
        _to_rpn(root->get_right().get(), formula);
        formula += root->get_token();
        return;
    }
}

static void handle_negation(Node* node) {
    if (node == nullptr)
        return;
    if (node->get_type() == UNARY && node->get_left() && node->get_left()->get_type() == UNARY) {
        if (node->get_left()->get_left() != nullptr) {
            std::unique_ptr<Node> operand_node = std::move(node->get_left()->get_left());
            node->set_type(operand_node->get_type());
            node->set_token(operand_node->get_token());
            node->set_left(operand_node->get_left() ? std::make_unique<Node>(*operand_node->get_left()) : nullptr);
            node->set_right(operand_node->get_right() ? std::make_unique<Node>(*operand_node->get_right()) : nullptr);
        }
    }
    if (node->get_type() == UNARY) {
        node->set_type(OPERAND);
        node->set_token((node->get_left()->get_token() + "!"));
        node->set_left(nullptr);
        node->set_right(nullptr);
    }
    handle_negation(node->get_right().get());
    handle_negation(node->get_left().get());
}

static void handle_unary(Node* node) {
    if (node == nullptr)
        return;
    if (node->get_type() == UNARY && node->get_left()->get_type() == BINARY) {
        std::unique_ptr<Node> saved_tree = std::make_unique<Node>(node->get_left()->get_token(),
            std::move(node->get_left()->get_left()), std::move(node->get_left()->get_right()));
        switch (node->get_left()->get_token()[0]) {
            case '&':
                node->set_type(BINARY);
                node->set_token("|");
                node->set_left(std::make_unique<Node>("!", std::move(saved_tree->get_left())));
                node->set_right(std::make_unique<Node>("!", std::move(saved_tree->get_right())));
                break;
            case '|':
                node->set_type(BINARY);
                node->set_token("&");
                node->set_left(std::make_unique<Node>("!", std::move(saved_tree->get_left())));
                node->set_right(std::make_unique<Node>("!", std::move(saved_tree->get_right())));
                break;
            default:
                throw std::runtime_error("Handle unary: Invalid binary token");
        }
    }
    handle_unary(node->get_right().get());
    handle_unary(node->get_left().get());
}

static void handle_binary(Node* node) {
    if (node == nullptr)
        return;
    if (node->get_type() == BINARY
        && (node->get_token() == ">" || node->get_token() == "=" || node->get_token() == "^")) {
        if (node->get_right() == nullptr || node->get_left() == nullptr)
            throw std::runtime_error("Invalid binary token: absense right and/or left node");
        std::unique_ptr<Node> saved_tree = std::make_unique<Node>(node->get_left()->get_token(),
            std::move(node->get_left()), std::move(node->get_right()));
        switch (node->get_token()[0]) {
            case '>':
                node->set_type(BINARY);
                node->set_token("|");
                node->set_left(std::make_unique<Node>("!", std::move(*saved_tree->get_left())));
                node->set_right(std::make_unique<Node>(std::move(*saved_tree->get_right())));
                break;
            case '=':
                node->set_type(BINARY);
                node->set_token("|");
                node->set_left(std::make_unique<Node>("&",
                    std::make_unique<Node>(*saved_tree->get_left()),
                    std::make_unique<Node>(*saved_tree->get_right())));
                node->set_right(std::make_unique<Node>("&",
                    std::make_unique<Node>("!", *saved_tree->get_left()),
                    std::make_unique<Node>("!", *saved_tree->get_right())));
                saved_tree.reset();
                break;
            case '^':
                node->set_type(BINARY);
                node->set_token("|");
                node->set_left(std::make_unique<Node>("&",
                    std::make_unique<Node>(*saved_tree->get_left()),
                    std::make_unique<Node>("!",*saved_tree->get_right())));
                node->set_right(std::make_unique<Node>("&",
                    std::make_unique<Node>("!", *saved_tree->get_left()),
                    std::make_unique<Node>(*saved_tree->get_right())));
                saved_tree.reset();
                break;              
        }
    }
    handle_binary(node->get_right().get());
    handle_binary(node->get_left().get());
}

bool NNF::_is_nnf(const Node* node) const {
    if (node == nullptr) {
        return true;
    } else if (node->get_type() == OPERAND) {
        return true;
    } else if (node->get_type() == UNARY) {
        return false;
    } else if (node->get_type() == BINARY) {
        if (node->get_token() == "&" || node->get_token() == "|")
            return _is_nnf(node->get_left().get()) && _is_nnf(node->get_right().get());
        else
            return false;
    }
    return false;
}

void NNF::_to_nnf(Node* root) {
    if (_is_nnf(root))
        return;
    handle_binary(root);
    handle_unary(root);
    handle_negation(root);
    if (_is_nnf(root) == false)
        throw std::logic_error("Wrong conversion to NNF");
}

void NNF::print_ast(const Node* node, const std::string& prefix) const {
    if (node == nullptr)
        return;
    std::cout << prefix << "`-- " << node->get_token() << std::endl;
    switch (node->get_type()) {
        case UNARY:
            print_ast(node->get_left().get(), prefix + "    ");
            break;
        case BINARY:
            print_ast(node->get_right().get(), prefix + "    ");
            print_ast(node->get_left().get(), prefix + "    ");
            break;
        default:
            break;
    }
}

const std::string& NNF::get_formula() const {
    return _formula;
}

const std::string& NNF::get_nnf() const {
    return _nnf_rpn;
}
