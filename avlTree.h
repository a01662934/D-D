#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

template <typename T> class Nodo {
private:
  T data;
  Nodo<T> *left;
  Nodo<T> *right;
  int height; 

  template <typename U> friend class AVL;

public:
  Nodo(T data) {
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
    this->height = 1;
  }
};

template <typename T> class AVL {
private:
  Nodo<T> *rotateRightLeft(Nodo<T> *node) { 
    if (node->right != nullptr) {
      node->right = rotateRight(node->right);
    }
    return rotateLeft(node);
  }

  Nodo<T> *rotateLeftRight(Nodo<T> *node) { 
    if (node->left != nullptr) {
      node->left = rotateLeft(node->left);
    }
    return rotateRight(node);
  }

  Nodo<T> *root;

  int getHeight(Nodo<T> *node) {
    return (node != nullptr) ? node->height : 0;
  } // O(1)

  int getBalanceFactor(Nodo<T> *node) { 
    if (node == nullptr) {
      return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
  }

  void updateHeight(Nodo<T> *node) {
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
  }

  Nodo<T> *rotateRight(Nodo<T> *y) {
    Nodo<T> *x = y->left;
    Nodo<T> *T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
  }

  Nodo<T> *rotateLeft(Nodo<T> *x) { 
    Nodo<T> *y = x->right;
    Nodo<T> *T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
  }

  void insert(Nodo<T> *&node, T data) { // O(log n)
    if (node == nullptr) {
      node = new Nodo<T>(data);
    } else {
      if (data < node->data) {
        insert(node->left, data);
      } else if (data > node->data) {
        insert(node->right, data);
      } else {
        return;
      }

      updateHeight(node);

      int balance = getBalanceFactor(node);

      if (balance > 1 && data < node->left->data) { 
        node = rotateRight(node);
      } else if (balance < -1 && data > node->right->data) {
        node = rotateLeft(node);
      } else if (balance > 1 && data > node->left->data) { 
        node = rotateLeftRight(node);
      } else if (balance < -1 && data < node->right->data) {
        node = rotateRightLeft(node);
      }
    }
  }

  void inOrden(Nodo<T> *node) { //  O(n)
    if (node != nullptr) {
      inOrden(node->left);
      cout << node->data << " : ";
      inOrden(node->right);
    }
  }

  void preOrden(Nodo<T> *node) { //  O(n)
    if (node != nullptr) {
      cout << node->data << " : ";
      preOrden(node->left);
      preOrden(node->right);
    }
  }

  void postOrden(Nodo<T> *node) { // O(n)
    if (node != nullptr) {
      postOrden(node->left);
      postOrden(node->right);
      cout << node->data << " : ";
    }
  }

  bool contains(Nodo<T> *node, T data) { //  O(log n)
    if (node == nullptr) {
      return false;
    } else {
      if (data == node->data) {
        return true;
      } else if (data < node->data) {
        return contains(node->left, data);
      } else {
        return contains(node->right, data);
      }
    }
  }

  T max(Nodo<T> *node) { // O(log n)
    if (node->right == nullptr) {
      return node->data;
    }
    return max(node->right);
  }

  T min(Nodo<T> *node) { // O(log n)
    if (node->left == nullptr) {
      return node->data;
    }
    return min(node->left);
  }

  int length(Nodo<T> *node) { // O(n)
    if (node == nullptr) {
      return 0;
    }
    int leftCounter = length(node->left);
    int rightCounter = length(node->right);
    return leftCounter + rightCounter + 1;
  }

public:
  AVL() { root = nullptr; }
  bool isEmpty() { return (root == nullptr); }

  void inOrden() { inOrden(root); }

  void preOrden() { preOrden(root); }

  void postOrden() { postOrden(root); }

  void insert(T data) {
    if (isEmpty()) { 
      root = new Nodo<T>(data);
    } else {
      insert(root, data);
    }
  }

  bool contains(T data) { return contains(root, data); }

  T max() { return max(root); }

  T min() { return min(root); }

  int length() { return length(root); }
};
