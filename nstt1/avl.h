#ifndef AVL_H_
#define AVL_H_

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>

template<std::totally_ordered T>
class AVLTree {
  struct Node {
    Node* parent;
    Node* left;
    Node* right;
    std::intmax_t height;
    T value;

    Node(const T& value):
        parent(nullptr), left(nullptr), right(nullptr), height(0), value(value) {}

    Node(const Node& other, Node* par = nullptr):
        parent(par),
        left(other.left ? new Node(*other.left, this) : nullptr),
        right(other.right ? new Node(*other.right, this) : nullptr),
        height(other.height),
        value(other.value) {
    }

    ~Node() {
      delete left;
      delete right;
    }

    intmax_t balance(void) {
      return (right ? right->height : -1) - (left ? left->height : -1);
    }

    Node* small_left_turn(void) {
      Node& b  = *right;
      b.parent = parent;
      parent   = right;

      right         = b.left;
      right->parent = this;

      b.left = this;

      height   = std::max(left->height, right->height) + 1;
      b.height = std::max(height, b.right->height) + 1;
      return &b;
    }

    Node* small_right_turn(void) {
      Node& b  = *left;
      b.parent = parent;
      parent   = left;

      left         = b.right;
      left->parent = this;

      b.right = this;

      height   = std::max(left->height, right->height) + 1;
      b.height = std::max(b.left->height, height) + 1;
      return &b;
    }

    Node* big_left_turn(void) {
      right = right->small_left_turn();
      return small_left_turn();
    }

    Node* big_right_turn(void) {
      left = left->small_right_turn();
      return small_right_turn();
    }

    Node* repair(void) {
      if (balance() == 2) {
        if (right->balance() >= 0) {
          return small_left_turn();
        } else {
          return big_left_turn();
        }
      } else if (balance() == -2) {
        if (left->balance() <= 0) {
          return small_right_turn();
        } else {
          return big_right_turn();
        }
      }
      return this;
    }

    Node& min(void) {
      if (left)
        return left->min();
      return *this;
    }

    Node& max(void) {
      if (right)
        return right->max();
      return *this;
    }

    Node* insert(T v) {
      if (v < value) {
        if (left) {
          left = left->insert(v);
        } else {
          left = new Node(v);
        }
      } else {
        if (right) {
          right = right->insert(v);
        } else {
          right = new Node(v);
        }
      }
      return repair();
    }

    Node* replace_with_min(Node* node) {
      if (left) {
        left = left->replace_with_min(node);
        return repair();
      }
      if (right) {
        right->parent = parent;
      }
      Node* ret = right;
      parent    = node->parent;
      left      = node->left;
      right     = node->right;
      height    = node->height;

      node->parent = this;
      return ret;
    }

    Node* remove(T v) {
      if (v != value) {
        if (v < value) {
          if (left)
            left = left->remove(v);
        } else {
          if (right)
            right = right->remove(v);
        }
        return repair();
      } else {
        if (!left && !right) {
          delete this;
          return nullptr;
        } else if (left && right) {
          Node* node    = right->replace_with_min(this);
          parent->right = node; // MIN node that took our place, not actual parent

          left  = nullptr;
          right = nullptr;
          delete this;

          return node->repair();
        } else {
          Node* tail   = left ? left : right;
          tail->parent = parent;

          left  = nullptr;
          right = nullptr;
          delete this;

          return tail;
        }
      }
    }
  };

  Node* root;

public:
  AVLTree():
      root(nullptr) {}

  AVLTree(const AVLTree<T>& other):
      root(other.root ? new Node(*other.root) : nullptr) {}

  AVLTree<T>& operator=(const AVLTree<T>& other) {
    delete root;
    root = other.root ? new Node(*other.root) : nullptr;
    return *this;
  }

  ~AVLTree() {
    delete root;
  }

  void insert(T v) {
    if (root)
      root = root->insert(v);
    else
      root = new Node(v);
  }

  void remove(T v) {
    root = root->remove(v);
  }

  //? find
  //todo T select(std::size_t) const;

  T min(void) const {
    if (root)
      return root->min().value;
    throw std::out_of_range("Tree is empty");
  }

  T max(void) const {
    if (root)
      return root->max().value;
    throw std::out_of_range("Tree is empty");
  }

  // T predecessor(const T&) const;
  // T successor(const T&) const;
  // std::size_t rank(const T&) const;
  //todo iterators
};

#endif
