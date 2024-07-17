#include "FingerTree.h"
#include "Metrics.h"
#include <chrono>
#include <thread>
#include <algorithm> // Para std::max

int FingerTree::height(FingerNode* node) {
    return node ? node->height : 0;
}

int FingerTree::getBalance(FingerNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

FingerNode* FingerTree::rightRotate(FingerNode* y) {
    FingerNode* x = y->left;
    FingerNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

FingerNode* FingerTree::leftRotate(FingerNode* x) {
    FingerNode* y = x->right;
    FingerNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

Metrics FingerTree::insert(int value) {
    Metrics metrics = {"FingerTreeInsert", "Unknown", 0, 0, 0, 0.0};
    auto start = std::chrono::high_resolution_clock::now();

    root = insert(root, value, metrics);

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}

FingerNode* FingerTree::insert(FingerNode* node, int value, Metrics& metrics) {
    if (node == nullptr) {
        metrics.movements++;
        return new FingerNode(value);
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
        return rightRotate(node);
    }

    if (balance < -1 && value > node->right->data) {
        return leftRotate(node);
    }

    if (balance > 1 && value > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && value < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Metrics FingerTree::search(int value) {
    Metrics metrics = {"FingerTreeSearch", "Unknown", 0, 0, 0, 0.0};
    auto start = std::chrono::high_resolution_clock::now();

    search(root, value, metrics);
    
    // Adicionar pausa para garantir a medição de tempo
    std::this_thread::sleep_for(std::chrono::microseconds(1));

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}

FingerNode* FingerTree::search(FingerNode* node, int value, Metrics& metrics) {
    metrics.comparisons++;
    if (node == nullptr || node->data == value) {
        return node;
    }
    if (value < node->data) {
        return search(node->left, value, metrics);
    } else {
        return search(node->right, value, metrics);
    }
}

Metrics FingerTree::remove(int value) {
    Metrics metrics = {"FingerTreeRemove", "Unknown", 0, 0, 0, 0.0};
    auto start = std::chrono::high_resolution_clock::now();

    root = remove(root, value, metrics);

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}

FingerNode* FingerTree::remove(FingerNode* node, int value, Metrics& metrics) {
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
            FingerNode* temp = node->left ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            FingerNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data, metrics);
        }
    }

    if (node == nullptr) return node;

    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0) {
        return rightRotate(node);
    }

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0) {
        return leftRotate(node);
    }

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

FingerNode* FingerTree::findMin(FingerNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
