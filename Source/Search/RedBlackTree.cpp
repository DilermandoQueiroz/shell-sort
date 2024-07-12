#include "redBlackTree.h"
#include <chrono>

Metrics RedBlackTree::insert(int value) {
    Metrics metrics = {0, 0, 0.0};
    auto start = std::chrono::high_resolution_clock::now();

    root = insert(root, value, metrics);

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}

RBNode* RedBlackTree::insert(RBNode* node, int value, Metrics& metrics) {
    if (node == nullptr) {
        metrics.movements++;
        RBNode* newNode = new RBNode(value);
        if (root == nullptr) {
            root = newNode;
            root->color = BLACK;
        }
        return newNode;
    }

    metrics.comparisons++;
    if (value < node->data) {
        RBNode* leftChild = insert(node->left, value, metrics);
        node->left = leftChild;
        leftChild->parent = node;
    } else if (value > node->data) {
        RBNode* rightChild = insert(node->right, value, metrics);
        node->right = rightChild;
        rightChild->parent = node;
    }

    insertFixUp(node, metrics);

    return node;
}

void RedBlackTree::insertFixUp(RBNode* node, Metrics& metrics) {
    while (node != root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            RBNode* uncle = node->parent->parent->right;
            if (uncle && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(node, metrics);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(node->parent->parent, metrics);
            }
        } else {
            RBNode* uncle = node->parent->parent->left;
            if (uncle && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(node, metrics);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotate(node->parent->parent, metrics);
            }
        }
    }
    root->color = BLACK;
}

Metrics RedBlackTree::search(int value) {
    Metrics metrics = {0, 0, 0.0};
    auto start = std::chrono::high_resolution_clock::now();

    search(root, value, metrics);

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}

RBNode* RedBlackTree::search(RBNode* node, int value, Metrics& metrics) {
    while (node != nullptr) {
        metrics.comparisons++;
        if (node->data == value) {
            return node;
        } else if (value < node->data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return nullptr;
}

Metrics RedBlackTree::remove(int value) {
    Metrics metrics = {0, 0, 0.0};
    auto start = std::chrono::high_resolution_clock::now();

    root = remove(root, value, metrics);

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}

RBNode* RedBlackTree::remove(RBNode* node, int value, Metrics& metrics) {
    if (node == nullptr) {
        return node;
    }

    metrics.comparisons++;
    if (value < node->data) {
        node->left = remove(node->left, value, metrics);
    } else if (value > node->data) {
        node->right = remove(node->right, value, metrics);
    } else {
        RBNode* y = node;
        Color yOriginalColor = y->color;
        RBNode* x = nullptr;

        if (node->left == nullptr) {
            x = node->right;
            transplant(node, node->right, metrics);
        } else if (node->right == nullptr) {
            x = node->left;
            transplant(node, node->left, metrics);
        } else {
            y = findMin(node->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == node) {
                if (x) x->parent = y;
            } else {
                transplant(y, y->right, metrics);
                y->right = node->right;
                if (y->right) y->right->parent = y;
            }
            transplant(node, y, metrics);
            y->left = node->left;
            if (y->left) y->left->parent = y;
            y->color = node->color;
        }

        delete node;

        if (yOriginalColor == BLACK) {
            removeFixUp(x, y->parent, metrics);
        }
    }

    return root;
}

void RedBlackTree::removeFixUp(RBNode* x, RBNode* parent, Metrics& metrics) {
    while (x != root && (!x || x->color == BLACK)) {
        if (x == parent->left) {
            RBNode* w = parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                parent->color = RED;
                leftRotate(parent, metrics);
                w = parent->right;
            }
            if ((!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK)) {
                w->color = RED;
                x = parent;
                parent = x->parent;
            } else {
                if (!w->right || w->right->color == BLACK) {
                    if (w->left) w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w, metrics);
                    w = parent->right;
                }
                w->color = parent->color;
                parent->color = BLACK;
                if (w->right) w->right->color = BLACK;
                leftRotate(parent, metrics);
                x = root;
            }
        } else {
            RBNode* w = parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                parent->color = RED;
                rightRotate(parent, metrics);
                w = parent->left;
            }
            if ((!w->right || w->right->color == BLACK) && (!w->left || w->left->color == BLACK)) {
                w->color = RED;
                x = parent;
                parent = x->parent;
            } else {
                if (!w->left || w->left->color == BLACK) {
                    if (w->right) w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w, metrics);
                    w = parent->left;
                }
                w->color = parent->color;
                parent->color = BLACK;
                if (w->left) w->left->color = BLACK;
                rightRotate(parent, metrics);
                x = root;
            }
        }
    }
    if (x) x->color = BLACK;
}

RBNode* RedBlackTree::findMin(RBNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void RedBlackTree::leftRotate(RBNode* x, Metrics& metrics) {
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    metrics.movements++;
}

void RedBlackTree::rightRotate(RBNode* x, Metrics& metrics) {
    RBNode* y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
    metrics.movements++;
}

void RedBlackTree::transplant(RBNode* u, RBNode* v, Metrics& metrics) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
    metrics.movements++;
}