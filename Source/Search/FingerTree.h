#ifndef FINGERTREE_H
#define FINGERTREE_H

#include "Metrics.h"

struct FingerTreeNode {
    int value;
    FingerTreeNode* left;
    FingerTreeNode* right;
    FingerTreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class FingerTree {
private:
    FingerTreeNode* root;
    FingerTreeNode* insert(FingerTreeNode* node, int value, Metrics& metrics);
    FingerTreeNode* search(FingerTreeNode* node, int value, Metrics& metrics);
    FingerTreeNode* remove(FingerTreeNode* node, int value, Metrics& metrics);
    FingerTreeNode* findMin(FingerTreeNode* node);

public:
    FingerTree() : root(nullptr) {}
    Metrics insert(int value);
    Metrics search(int value);
    Metrics remove(int value);
};

#endif
