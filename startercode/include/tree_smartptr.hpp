#pragma once
#include <iostream>
#include <memory>
#include <functional>
#include <initializer_list>

template<typename T>
class Tree {
private:
    struct Node {
        Node(std::shared_ptr<const Node> lft, 
             T val, 
             std::shared_ptr<const Node> rgt,
             std::weak_ptr<const Node> par = std::weak_ptr<const Node>())
        : _lft(lft), _val(val), _rgt(rgt), _parent(par) {}

        std::shared_ptr<const Node> _lft;
        T _val;
        std::shared_ptr<const Node> _rgt;
        std::weak_ptr<const Node> _parent;  // Parent pointer (weak to avoid cycles)
    };

    explicit Tree(std::shared_ptr<const Node> node) : _root(node) {}

public:
    Tree() : _root(nullptr) {}
    Tree(Tree const & other) = default;
    Tree & operator=(Tree const & other) = default;
    ~Tree() = default;
    Tree(Tree && other) = default;
    Tree & operator=(Tree && other) = default;

    Tree(Tree lft, T val, Tree rgt) {
        auto newNode = std::make_shared<Node>(lft._root, val, rgt._root);
        
        // Set parent pointers for children
        if (lft._root) {
            const_cast<Node*>(lft._root.get())->_parent = newNode;
        }
        if (rgt._root) {
            const_cast<Node*>(rgt._root.get())->_parent = newNode;
        }
        
        _root = newNode;
    }

    Tree(std::initializer_list<T> init) : Tree() {
        for (const auto& val : init) {
            *this = insert(val);
        }
    }

    bool isEmpty() const {
        return _root == nullptr;
    }

    size_t size() const {
        if (isEmpty()) return 0;
        return 1 + left().size() + right().size();
    }

    T root() const {
        if (isEmpty()) {
            throw std::runtime_error("root() called on empty tree");
        }
        return _root->_val;
    }

    Tree left() const {
        if (isEmpty()) {
            return Tree();
        }
        return Tree(_root->_lft);
    }

    Tree right() const {
        if (isEmpty()) {
            return Tree();
        }
        return Tree(_root->_rgt);
    }
    
    // Get parent tree (if exists)
    Tree parent() const {
        if (isEmpty() || _root->_parent.expired()) {
            return Tree();  // No parent or root node
        }
        return Tree(_root->_parent.lock());
    }
    
    // Check if this is the root (has no parent)
    bool isRoot() const {
        if (isEmpty()) return false;
        return _root->_parent.expired();
    }

    // Check if this is a leaf (no children)
    bool isLeaf() const {
        if (isEmpty()) return false;
        return left().isEmpty() && right().isEmpty();
    }

    template <typename Compare = std::less<T>>
    Tree insert(T x, Compare comp = std::less<T>()) const {
        if (isEmpty()) {
            return Tree(Tree(), x, Tree());
        }
        T y = root();
        if (comp(x, y)) {
            auto newLeft = left().insert(x, comp);
            return Tree(newLeft, y, right());
        } else if (comp(y, x)) {
            auto newRight = right().insert(x, comp);
            return Tree(left(), y, newRight);
        } else {
            return *this;  // No duplicates
        }
    }

    template <typename Compare = std::less<T>>
    bool member(T x, Compare comp = std::less<T>()) const {
        if (isEmpty()) {
            return false;
        }
        T y = root();
        if (comp(x, y)) {
            return left().member(x, comp);
        } else if (comp(y, x)) {
            return right().member(x, comp);
        } else {
            return true;
        }
    }

    template<typename Compare = std::less<T>>
    bool find(T x, Tree &subtreeWhereFound, Compare comp = std::less<T>()) const {
        if (isEmpty()) {
            subtreeWhereFound = Tree();
            return false;
        }
        T y = root();
        if (comp(x, y)) {
            return left().find(x, subtreeWhereFound, comp);
        } else if (comp(y, x)) {
            return right().find(x, subtreeWhereFound, comp);
        } else {
            subtreeWhereFound = *this;
            return true;
        }
    }

    void preorder(std::function<void(T)> visit) const {
        if (isEmpty()) return;
        T contents = root();
        visit(contents);
        left().preorder(visit);
        right().preorder(visit);
    }

    void inorder(std::function<void(T)> visit) const {
        if (isEmpty()) return;
        left().inorder(visit);
        T contents = root();
        visit(contents);
        right().inorder(visit);
    }

    void postorder(std::function<void(T)> visit) const {
        if (isEmpty()) return;
        left().postorder(visit);
        right().postorder(visit);
        T contents = root();
        visit(contents);
    }

private:
    std::shared_ptr<const Node> _root;
};