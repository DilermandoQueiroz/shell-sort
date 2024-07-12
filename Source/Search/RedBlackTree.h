#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "Metrics.h"

// Definição de cor para os nós da árvore
enum Color { RED, BLACK };

// Estrutura para o nó da árvore Red-Black
struct RBNode {
    int data;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;

    RBNode(int value) : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Classe para a Árvore Red-Black
class RedBlackTree {
public:
    RedBlackTree() : root(nullptr) {}

    Metrics insert(int value);
    Metrics search(int value);
    Metrics remove(int value);

private:
    RBNode* root;

    void insertFixUp(RBNode* node, Metrics& metrics);
    void removeFixUp(RBNode* node, RBNode* parent, Metrics& metrics);

    RBNode* insert(RBNode* node, int value, Metrics& metrics);
    RBNode* search(RBNode* node, int value, Metrics& metrics);
    RBNode* remove(RBNode* node, int value, Metrics& metrics);

    RBNode* findMin(RBNode* node);

    void leftRotate(RBNode* node, Metrics& metrics);
    void rightRotate(RBNode* node, Metrics& metrics);
    void transplant(RBNode* u, RBNode* v, Metrics& metrics);

    void deleteNode(RBNode* node);
};

#endif // REDBLACKTREE_H