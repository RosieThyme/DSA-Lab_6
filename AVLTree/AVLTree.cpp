#include <iostream>
#include "AVLNode.h"
#include "AVLTree.h"

void AVLTree::RotateRight(AVLNode* node) {
    AVLNode* parent = node->GetParent();
    AVLNode* leftChild = node->GetLeft();
    AVLNode* leftRightChild = leftChild->GetRight();

    node->SetLeft(leftRightChild);
    leftChild->SetRight(node);

    if (parent) {
        parent->ReplaceChild(node, leftChild);
    }
    else {
        root = leftChild;
        root->SetParent(nullptr);
    }
}

void AVLTree::RotateLeft(AVLNode* node) {
    AVLNode* parent = node->GetParent();
    AVLNode* rightChild = node->GetRight();
    AVLNode* rightLeftChild = rightChild->GetLeft();

    node->SetRight(rightLeftChild);
    rightChild->SetLeft(node);

    if (parent) {
        parent->ReplaceChild(node, rightChild);
    }
    else {
        root = rightChild;
        root->SetParent(nullptr);
    }
}

void AVLTree::Rebalance(AVLNode* node) {
    // First update the height of this node
    node->UpdateHeight();

    // Check for an imbalance
    if (node->GetBalance() == -2) {
        // The subtree is too big to the right
        if (node->GetRight()->GetBalance() == 1) {
            // Double rotation case. First do a right rotation
            // on the right child
            RotateRight(node->GetRight());
        }

        // Left rotation makes the subtree balanced
        RotateLeft(node);
    }
    else if (node->GetBalance() == 2) {
        // The subtree is too big to the left
        if (node->GetLeft()->GetBalance() == -1) {
            // Double rotation case. First do a left rotation
            // on the left child
            RotateLeft(node->GetLeft());
        }

        // Right rotation makes the subtree balanced
        RotateRight(node);
    }
}

void AVLTree::InsertKey(const std::string &name) {
    if (!Contains(name)) {
        InsertNode(new AVLNode(name));
    }
}

void AVLTree::InsertNode(AVLNode* node) {
    // static makes sure new heap is only created at the beginning
    // Check if tree is empty
    if (!root) {
        root = node;
        // create heap when you have the 1st element
    }
    else {
        // Step 1 - do a regular binary search tree insert
        AVLNode* currentNode = root;
        while (currentNode) {
            // Choose to go left or right
            if (node->GetName() < currentNode->GetName()) {
                // Go left. If left child is null, insert the new
                // node here
                if (currentNode->GetLeft() == nullptr) {
                    currentNode->SetLeft(node);
                    currentNode = nullptr;
                }
                else {
                    // Go left and do the loop again
                    currentNode = currentNode->GetLeft();
                }
            }
            else {
                // Go right. If the right child is null, insert the
                // new node here
                if (currentNode->GetRight() == nullptr) {
                    currentNode->SetRight(node);
                    currentNode = nullptr;
                }
                else {
                    // Go right and do the loop again
                    currentNode = currentNode->GetRight();
                }
            }
        }

        // Step 2 - Rebalance along a path from the new node's parent up
        // to the root
        node = node->GetParent();
        while (node) {
            Rebalance(node);
            node = node->GetParent();
        }
    }
}

bool AVLTree::RemoveNode(AVLNode* nodeToRemove) {
    // Base case:
    if (!nodeToRemove) {
        return false;
    }

    // nodeToRemove's parent is needed for rebalancing
    AVLNode* parent = nodeToRemove->GetParent();

    // Case 1: Internal node with 2 children
    if (nodeToRemove->GetLeft() && nodeToRemove->GetRight()) {
        // Find successor
        AVLNode* successorNode = nodeToRemove->GetRight();
        while (successorNode->GetLeft()) {
            successorNode = successorNode->GetLeft();
        }

        // Copy the value from the node
        nodeToRemove->SetKey(successorNode->GetName());

        // Recursively remove successor
        RemoveNode(successorNode);

        // Nothing left to do since the recursive call will have rebalanced
        return true;
    }

    // Case 2: Root node (with 1 or 0 children)
    else if (nodeToRemove == root) {
        if (nodeToRemove->GetLeft()) {
            root = nodeToRemove->GetLeft();
        }
        else {
            root = nodeToRemove->GetRight();
        }

        if (root) {
            root->SetParent(nullptr);
        }

        delete nodeToRemove;
        return true;
    }

    // Case 3: Internal with left child only
    else if (nodeToRemove->GetLeft()) {
        parent->ReplaceChild(nodeToRemove, nodeToRemove->GetLeft());
    }

    // Case 4: Internal with right child only OR leaf
    else {
        parent->ReplaceChild(nodeToRemove, nodeToRemove->GetRight());
    }

    // nodeToRemove is removed from the tree and can be deleted
    delete nodeToRemove;

    // Anything that was below nodeToRemove that has persisted is already
    // correctly balanced, but ancestors of nodeToRemove may need rebalancing.
    AVLNode* nodeToRebalance = parent;
    while (nodeToRebalance) {
        Rebalance(nodeToRebalance);
        nodeToRebalance = nodeToRebalance->GetParent();
    }

    return true;
}

bool AVLTree::Contains(const std::string &key) {
    AVLNode* currentNode = root;

    while (currentNode) {
        if (currentNode->GetName() == key) {
            return true;
        }
        if (currentNode->GetName() < key) {
            currentNode = currentNode->GetLeft();
        }
        else {
            currentNode = currentNode->GetRight();
        }
    }
    return false;
}

void AVLTree::PrintTree() {
    std::cout << std::endl;
    PrintHelper(root);
    std::cout << std::endl << "----------------------" << std::endl;
}

void AVLTree::PrintHelper(AVLNode *node) {
    // Order: Left, Root, Right
    if (node == nullptr) {
        return;
    }
    PrintHelper(node->GetLeft());
    std::cout << node->GetName() << ", ";
    PrintHelper(node->GetRight());
}
