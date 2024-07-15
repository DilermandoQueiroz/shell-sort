#include "BinarySearchTree.h"
#include <chrono>

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    destroyTree(root);
}

void BinarySearchTree::destroyTree(Node* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

Metrics BinarySearchTree::insert(int value) {
    Metrics metrics;
    auto start = std::chrono::high_resolution_clock::now();

    root = insert(root, value, metrics);

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}

BinarySearchTree::Node* BinarySearchTree::insert(Node* node, int value, Metrics& metrics) {
    if (!node) {
        metrics.movements++;
        return new Node(value);
    }

    metrics.comparisons++;
    if (value < node->data) {
        node->left = insert(node->left, value, metrics);
    } else {
        node->right = insert(node->right, value, metrics);
    }
    return node;
}

Metrics BinarySearchTree::search(int value) {
    Metrics metrics;
    auto start = std::chrono::high_resolution_clock::now();

    search(root, value, metrics);

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}

BinarySearchTree::Node* BinarySearchTree::search(Node* node, int value, Metrics& metrics) {
    if (!node) return nullptr;

    metrics.comparisons++;
    if (node->data == value) {
        return node;
    } else if (value < node->data) {
        return search(node->left, value, metrics);
    } else {
        return search(node->right, value, metrics);
    }
}

Metrics BinarySearchTree::remove(int value) {
    Metrics metrics;
    auto start = std::chrono::high_resolution_clock::now();

    root = remove(root, value, metrics);

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}

BinarySearchTree::Node* BinarySearchTree::remove(Node* node, int value, Metrics& metrics) {
    if (!node) return nullptr;

    metrics.comparisons++;
    if (value < node->data) {
        node->left = remove(node->left, value, metrics);
    } else if (value > node->data) {
        node->right = remove(node->right, value, metrics);
    } else {
        metrics.movements++;
        if (!node->left) {
            Node* rightNode = node->right;
            delete node;
            return rightNode;
        } else if (!node->right) {
            Node* leftNode = node->left;
            delete node;
            return leftNode;
        } else {
            Node* minNode = findMin(node->right);
            node->data = minNode->data;
            node->right = remove(node->right, minNode->data, metrics);
        }
    }
    return node;
}

BinarySearchTree::Node* BinarySearchTree::findMin(Node* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}
