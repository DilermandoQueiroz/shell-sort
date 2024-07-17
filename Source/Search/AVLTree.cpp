#include "AVLTree.h"
#include "Metrics.h"
#include <chrono>
#include <algorithm>
#include <iostream> // Para depuração

int AVLTree::height(AVLNode* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

Metrics AVLTree::insert(int value) {
    Metrics metrics = {"AVLTreeInsert", "Unknown", 0, 0, 0, 0.0};
    auto start = std::chrono::high_resolution_clock::now();

    root = insert(root, value, metrics);

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cerr << "Insert - Comparisons: " << metrics.comparisons << ", Movements: " << metrics.movements << std::endl; // Log para depuração
    return metrics;
}

AVLNode* AVLTree::insert(AVLNode* node, int value, Metrics& metrics) {
    if (node == nullptr) {
        metrics.movements++;
        return new AVLNode(value);
    }
    metrics.comparisons++;
    if (value < node->data) {
        node->left = insert(node->left, value, metrics);
    } else if (value > node->data) {
        node->right = insert(node->right, value, metrics);
    } else {
        return node; // Valor duplicado não é inserido
    }

    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && value < node->left->data) {
        metrics.movements++; // Contabilizar o movimento
        return rightRotate(node);
    }

    if (balance < -1 && value > node->right->data) {
        metrics.movements++; // Contabilizar o movimento
        return leftRotate(node);
    }

    if (balance > 1 && value > node->left->data) {
        node->left = leftRotate(node->left);
        metrics.movements += 2; // Contabilizar o movimento
        return rightRotate(node);
    }

    if (balance < -1 && value < node->right->data) {
        node->right = rightRotate(node->right);
        metrics.movements += 2; // Contabilizar o movimento
        return leftRotate(node);
    }

    return node;
}

Metrics AVLTree::search(int value) {
    Metrics metrics = {"AVLTreeSearch", "Unknown", 0, 0, 0, 0.0};
    auto start = std::chrono::high_resolution_clock::now();

    AVLNode* result = search(root, value, metrics);

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cerr << "Search - Comparisons: " << metrics.comparisons << ", Movements: " << metrics.movements << ", Found: " << (result != nullptr) << std::endl; // Log para depuração
    return metrics;
}

AVLNode* AVLTree::search(AVLNode* node, int value, Metrics& metrics) {
    if (node == nullptr || node->data == value) {
        metrics.comparisons++;
        std::cerr << "Search - Node: " << (node ? node->data : -1) << ", Value: " << value << std::endl; // Log para depuração
        return node;
    }
    metrics.comparisons++;
    if (value < node->data) {
        return search(node->left, value, metrics);
    } else {
        return search(node->right, value, metrics);
    }
}

Metrics AVLTree::remove(int value) {
    Metrics metrics = {"AVLTreeRemove", "Unknown", 0, 0, 0, 0.0};
    auto start = std::chrono::high_resolution_clock::now();

    root = remove(root, value, metrics);

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cerr << "Remove - Comparisons: " << metrics.comparisons << ", Movements: " << metrics.movements << std::endl; // Log para depuração
    return metrics;
}

AVLNode* AVLTree::remove(AVLNode* node, int value, Metrics& metrics) {
    if (node == nullptr) {
        metrics.comparisons++;
        return node;
    }

    metrics.comparisons++;
    if (value < node->data) {
        node->left = remove(node->left, value, metrics);
    } else if (value > node->data) {
        node->right = remove(node->right, value, metrics);
    } else {
        metrics.movements++;
        if (node->left == nullptr || node->right == nullptr) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            AVLNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data, metrics);
        }
    }

    if (node == nullptr) return node;

    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0) {
        metrics.movements++; // Contabilizar o movimento
        return rightRotate(node);
    }

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        metrics.movements += 2; // Contabilizar o movimento
        return rightRotate(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0) {
        metrics.movements++; // Contabilizar o movimento
        return leftRotate(node);
    }

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        metrics.movements += 2; // Contabilizar o movimento
        return leftRotate(node);
    }

    return node;
}

AVLNode* AVLTree::findMin(AVLNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
