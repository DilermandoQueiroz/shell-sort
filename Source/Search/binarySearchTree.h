#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "Metrics.h"

// Estrutura para o nó da árvore binária de busca
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Classe para a Árvore Binária de Busca
class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    Metrics insert(int value);
    Metrics search(int value);
    Metrics remove(int value);

private:
    Node* root;

    Node* insert(Node* node, int value, Metrics& metrics);
    Node* search(Node* node, int value, Metrics& metrics);
    Node* remove(Node* node, int value, Metrics& metrics);
    Node* findMin(Node* node);
};

#endif // BINARYSEARCHTREE_H