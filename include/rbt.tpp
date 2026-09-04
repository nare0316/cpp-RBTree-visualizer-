#include "rbt.hpp"
#include <iostream>

//insert
template <typename T>
void RBTree<T>::insert(const T &value) {
    Node<T> *new_node = new Node<T>(value);
    new_node->left = NIL;
    new_node->right = NIL;
    if (root == NIL) {
        root = new_node;
        root->color = Color::BLACK;
        root->parent = NIL;
        return;
    }
    Node<T> *tmp = root, *cur = NIL;
    while (tmp != NIL) {
        if (value < tmp->val) {
            cur = tmp;
            tmp = tmp->left;
        } else if (value > tmp->val) {
            cur = tmp;
            tmp = tmp->right;
        } else {
            delete new_node;
            return;
        }
    }
    if (value < cur->val) {
        cur->left = new_node;
    } else {
        cur->right = new_node;
    }

    new_node->parent = cur;

    fixInsert(new_node);
}
//////
template <typename T>
void RBTree<T>::fixInsert(Node<T> *node) {
    while (node->parent->color != Color::BLACK) {
        Node<T> *grandparent = node->parent->parent;
        Node<T> *uncle = nullptr;
        if (grandparent->right == node->parent) {
            uncle = grandparent->left;
        } else {
            uncle = grandparent->right;
        }

        if (uncle->color == Color::RED) {
            node->parent->color = Color::BLACK;
            uncle->color = Color::BLACK;
            grandparent->color = Color::RED;
            node = grandparent;
        } else {
            if (uncle == grandparent->left) {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotateRight(node);

                }
                rotateLeft(grandparent);
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rotateLeft(node);
                }
                rotateRight(grandparent);
            }
            node->parent->color = Color::BLACK;
            grandparent->color = Color::RED;
        }

    }
    root->color = Color::BLACK;
}

template <typename T>
void RBTree<T>::rotateLeft(Node<T> *x) {
    Node<T> *y = x->right;
    x->right = y->left;
    if (y->left != NIL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (y->parent == NIL) {
        root = y;
    } else {
        if (y->parent->left == x) {
            y->parent->left = y;
        } else {
            y->parent->right = y;
        }
    }
    y->left = x;
    x->parent = y;
}

template <typename T>
void RBTree<T>::rotateRight(Node<T> *x) {
    Node<T>* y = x->left;
    x->left = y->right;
    if (y->right != NIL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (y->parent == NIL) {
        root = y;
    } else {
        if (x->parent->left == x) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
    }
    y->right = x;
    x->parent = y;
}



template <typename T>
void RBTree<T>::transplant(Node<T> *u, Node<T> *v) {
    if (u->parent == NIL) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
    
}

template <typename T>
bool RBTree<T>::contains(const T& value) const {
    return search(value) != NIL;
}

template <typename T>
Node<T>* RBTree<T>::search(const T& value) const {
    Node<T> *tmp = root;
    while (tmp != NIL && tmp->val != value) {
        if (value < tmp->val) {
            tmp = tmp->left;
        } else {
            tmp = tmp->right;
        }
    }
    return tmp;
}

///delete
template <typename T>
void RBTree<T>::remove(const T& value) {
    Node<T> *z = search(value);
    if (z == NIL) {
        return;
    }
    Node<T> *y = z;
    Color original_color = y->color;
    Node<T> *x;
    if (y->left == NIL) {
        x = y->right;
        transplant(z, x);
    } else if (y->right == NIL) {
        x = y->left;
        transplant(z, x);
    } else {
        y = getMin(y->right);
        original_color = y->color;
        
        x = y->right;
        if (y->parent == z) {
            x->parent = y; 
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
  
    if (original_color == Color::BLACK) {
        deleteFixup(x);
    }
    delete z;
}

////

template <typename T>
void RBTree<T>::deleteFixup(Node<T> *x) {
    while (x != root && x->color == Color::BLACK) {
        if (x == x->parent->left) {
            Node<T> *sibling = x->parent->right;
            if (sibling->color == Color::RED) {
                sibling->color = Color::BLACK;
                x->parent->color = Color::RED;
                rotateLeft(x->parent);
                sibling = x->parent->right;
            }
            if (sibling->left->color == Color::BLACK && sibling->right->color == Color::BLACK) {
                sibling->color = Color::RED;
                x = x->parent;
            } else {
                if (sibling->right->color == Color::BLACK) {
                    sibling->left->color = Color::BLACK;
                    sibling->color = Color::RED;
                    rotateRight(sibling);
                    sibling = x->parent->right;
                }
                sibling->color = sibling->parent->color;
                sibling->parent->color = Color::BLACK;
                sibling->right->color = Color::BLACK;
                rotateLeft(x->parent);
                x = root;
            }
        } else {
            Node<T> *sibling = x->parent->left;
            if (sibling->color == Color::RED) {
                sibling->color = Color::BLACK;
                x->parent->color = Color::RED;
                rotateRight(x->parent);
                sibling = x->parent->left;
            }
            if (sibling->left->color == Color::BLACK && sibling->right->color == Color::BLACK) {
                sibling->color = Color::RED;
                x = x->parent;
            } else {
                if (sibling->left->color == Color::BLACK) {
                    sibling->right->color = Color::BLACK;
                    sibling->color = Color::RED;
                    rotateLeft(sibling);
                    sibling = x->parent->left;
                }
                sibling->color = sibling->parent->color;
                sibling->parent->color = Color::BLACK;
                sibling->left->color = Color::BLACK;
                rotateRight(x->parent);
                x = root;
            }

        }

    }
    x->color = Color::BLACK;
}


template <typename T>
Node<T>* RBTree<T>::getRoot() const {
    return root;
}

template <typename T>
Node<T>* RBTree<T>::getMin(Node<T> *node) const {
    Node<T> *tmp = node;
    while (tmp->left != NIL) {
        tmp = tmp->left;
    }
    return tmp;
}

template <typename T>
Node<T>* RBTree<T>::getMax(Node<T> *node) const {
    Node<T> *tmp = node;
    while (tmp->right != NIL) {
        tmp = tmp->right;
    }
    return tmp;

}


template <typename T>
Node<T>* RBTree<T>::getNIL() const {
    return NIL;
}


template <typename T>
void RBTree<T>::inorder() const {
    inorder_helper(root);
    std::cout << "\n";
}

template <typename T>
void RBTree<T>::preorder() const {
    preorder_helper(root);
    std::cout << "\n";

}

template <typename T>
void RBTree<T>::postorder() const {
    postorder_helper(root);
    std::cout << "\n";
}

template <typename T>
void RBTree<T>::inorder_helper(Node<T> *root) const {
    if (root == NIL) {
        return;
    }
    inorder_helper(root->left);
    std::cout << root->val << " ";
    inorder_helper(root->right);
}

template <typename T>
void RBTree<T>::preorder_helper(Node<T> *root) const {
    if (root == NIL) {
        return;
    }
    std::cout << root->val << " ";
    preorder_helper(root->left);
    preorder_helper(root->right);
}

template <typename T>
void RBTree<T>::postorder_helper(Node<T> *root) const {
    if (root == NIL) {
        return;
    }
    postorder_helper(root->left);
    postorder_helper(root->right);
    std::cout << root->val << " ";
}

template <typename T>
void RBTree<T>::destroy(Node<T> *root) {
    if (root == NIL) {
        return;
    }
    destroy(root->left);
    destroy(root->right);
    
    delete root;
}

template <typename T>
RBTree<T>::~RBTree() {
  destroy(root);
  delete NIL;
}
      
