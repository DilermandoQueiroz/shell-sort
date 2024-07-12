#include "BinarySearchTree.h"
#include <chrono>

Metrics BinarySearchTree::insert(int value) {
    Metrics metrics = {0, 0, 0.0};
    auto start = std::chrono::high_resolution_clock::now();

    root = insert(root, value, metrics);

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}

Node* BinarySearchTree::insert(Node* node, int value, Metrics& metrics) {
    if (node == nullptr) {
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
    Metrics metrics = {0, 0, 0.0};
    auto start = std::chrono::high_resolution_clock::now();

    search(root, value, metrics);

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}

Node* BinarySearchTree::search(Node* node, int value, Metrics& metrics) {
    if (node == nullptr || node->data == value) {
        metrics.comparisons++;
        return node;
    }
    metrics.comparisons++;
    if (value < node->data) {
        return search(node->left, value, metrics);
    } else {
        return search(node->right, value, metrics);
    }
}

Metrics BinarySearchTree::remove(int value) {
    Metrics metrics = {0, 0, 0.0};
    auto start = std::chrono::high_resolution_clock::now();

    root = remove(root, value, metrics);

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}

Node* BinarySearchTree::remove(Node* node, int value, Metrics& metrics) {
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
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        
        Node* temp = findMin(node->right);
        node->data = temp->data;
        node->right = remove(node->right, temp->data, metrics);
    }
    return node;
}

Node* BinarySearchTree::findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}