#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "Metrics.h"

class BinarySearchTree {
public:
    struct Node {
        int data;
        Node* left;
        Node* right;
        Node(int value) : data(value), left(nullptr), right(nullptr) {}
    };

    BinarySearchTree();
    ~BinarySearchTree();

    Metrics insert(int value);
    Metrics search(int value);
    Metrics remove(int value);

private:
    Node* root;
    void destroyTree(Node* node);
    Node* insert(Node* node, int value, Metrics& metrics);
    Node* search(Node* node, int value, Metrics& metrics);
    Node* remove(Node* node, int value, Metrics& metrics);
    Node* findMin(Node* node);
};

#endif // BINARY_SEARCH_TREE_H
