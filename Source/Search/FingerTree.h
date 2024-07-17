#ifndef FINGERTREE_H
#define FINGERTREE_H

#include "Metrics.h"

struct FingerNode {
    int data;
    FingerNode* left;
    FingerNode* right;
    int height;

    FingerNode(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

class FingerTree {
public:
    FingerTree() : root(nullptr) {}

    Metrics insert(int value);
    Metrics search(int value);
    Metrics remove(int value);

private:
    FingerNode* root;

    FingerNode* insert(FingerNode* node, int value, Metrics& metrics);
    FingerNode* search(FingerNode* node, int value, Metrics& metrics);
    FingerNode* remove(FingerNode* node, int value, Metrics& metrics);
    FingerNode* findMin(FingerNode* node);

    int height(FingerNode* node);
    int getBalance(FingerNode* node);

    FingerNode* rightRotate(FingerNode* y);
    FingerNode* leftRotate(FingerNode* x);
};

#endif // FINGERTREE_H
