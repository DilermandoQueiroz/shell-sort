#include "FingerTree.h"
#include <chrono>

Metrics FingerTree::insert(int value) {
    Metrics metrics;
    auto start = std::chrono::high_resolution_clock::now();
    root = insert(root, value, metrics);
    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}

FingerTreeNode* FingerTree::insert(FingerTreeNode* node, int value, Metrics& metrics) {
    if (node == nullptr) {
        return new FingerTreeNode(value);
    }
    metrics.comparisons++;
    if (value < node->value) {
        node->left = insert(node->left, value, metrics);
    } else if (value > node->value) {
        node->right = insert(node->right, value, metrics);
    }
    return node;
}

Metrics FingerTree::search(int value) {
    Metrics metrics;
    auto start = std::chrono::high_resolution_clock::now();
    search(root, value, metrics);
    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}

FingerTreeNode* FingerTree::search(FingerTreeNode* node, int value, Metrics& metrics) {
    if (node == nullptr) {
        return nullptr;
    }
    metrics.comparisons++;
    if (value == node->value) {
        return node;
    } else if (value < node->value) {
        return search(node->left, value, metrics);
    } else {
        return search(node->right, value, metrics);
    }
}

Metrics FingerTree::remove(int value) {
    Metrics metrics;
    auto start = std::chrono::high_resolution_clock::now();
    root = remove(root, value, metrics);
    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}

FingerTreeNode* FingerTree::remove(FingerTreeNode* node, int value, Metrics& metrics) {
    if (node == nullptr) {
        return nullptr;
    }
    metrics.comparisons++;
    if (value < node->value) {
        node->left = remove(node->left, value, metrics);
    } else if (value > node->value) {
        node->right = remove(node->right, value, metrics);
    } else {
        if (node->left == nullptr) {
            FingerTreeNode* rightNode = node->right;
            delete node;
            return rightNode;
        } else if (node->right == nullptr) {
            FingerTreeNode* leftNode = node->left;
            delete node;
            return leftNode;
        }
        FingerTreeNode* minNode = findMin(node->right);
        node->value = minNode->value;
        node->right = remove(node->right, minNode->value, metrics);
    }
    return node;
}

FingerTreeNode* FingerTree::findMin(FingerTreeNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
