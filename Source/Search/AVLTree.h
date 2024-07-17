#ifndef AVLTREE_H
#define AVLTREE_H

#include "Metrics.h"

// Estrutura para o nó da árvore AVL
struct AVLNode {
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

// Classe para a Árvore AVL
class AVLTree {
public:
    AVLTree() : root(nullptr) {}

    Metrics insert(int value);
    Metrics search(int value);
    Metrics remove(int value);

private:
    AVLNode* root;

    AVLNode* insert(AVLNode* node, int value, Metrics& metrics);
    AVLNode* search(AVLNode* node, int value, Metrics& metrics);
    AVLNode* remove(AVLNode* node, int value, Metrics& metrics);
    AVLNode* findMin(AVLNode* node);

    int height(AVLNode* node);
    int getBalance(AVLNode* node);

    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
};

#endif // AVLTREE_H
