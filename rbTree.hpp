#ifndef RBTREE_H
#define RBTREE_H

#include "rbNode.hpp"
#include <vector>

class rbTree {
private:
  rbNode *root, *nil;

  // Checks if the node is a left child or right child of its parent.
  bool isLeftChild(rbNode *node);
  bool isRightChild(rbNode *node);

  // Updates parent-child link by replacing old child with new child.
  void UpdateParentChildLink(rbNode *parent, rbNode *oldChild,
                             rbNode *newChild);

  // Performs a left rotation and right rotation on the given node.
  void rotateLeft(rbNode *node);
  void rotateRight(rbNode *node);

  // Returns the node with the minimum ride number in the subtree rooted at
  // node.
  rbNode *getMinimumNode(rbNode *node);

  // Rebalances the tree after inserting a new node.
  void insertionRebalance(rbNode *node);

  // Rebalances the tree after deleting a node.
  void DeletionRebalance(rbNode *node);

  // Searches for a node with the given ride number recursively starting from
  // the given root node.
  rbNode *searchRecursive(rbNode *root, int rideNumber);

  // Searches for all nodes with ride numbers in the given range recursively
  // starting from the given root node.
  void searchInRangeRecursive(rbNode *root, int rideNumber1, int rideNumber2,
                              std::vector<rbNode> &vec);

public:
  // Constructor and destructor for a new Red-Black Tree.
  rbTree();
  ~rbTree();

  // Inserts the given node into the tree.
  void insert(rbNode *node);

  // Deletes the given node from the tree.
  void deleteNode(rbNode *node);

  // Searches for a node with the given ride number in the tree.
  rbNode *search(int rideNumber);

  // Searches for all nodes with ride numbers in the given range.
  std::vector<rbNode> searchInRange(int rideNumber1, int rideNumber2);
};

#endif // RBTREE_H