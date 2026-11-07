#ifndef MAXHEAP_AVLTREE_H
#define MAXHEAP_AVLTREE_H
#include <string>
#include "AVLNode.h"

class AVLTree {
    AVLNode* root;

public:
    AVLTree() {
        root = nullptr;
    }

    void RotateRight(AVLNode* node);
    void RotateLeft(AVLNode* node);
    void Rebalance(AVLNode* node);
    void InsertKey(const std::string &key);
    void InsertNode(AVLNode* node);
    bool RemoveNode(AVLNode* nodeToRemove);
    bool Contains(const std::string &key);
    void PrintTree();
    void PrintHelper(AVLNode* node);
};


#endif //MAXHEAP_AVLTREE_H
