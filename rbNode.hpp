#ifndef RBNODE_H
#define RBNODE_H

#include <iostream>

// Enum for the possible colors of a node in a red-black tree.
enum class nodeColor { RED, BLACK };

// Forward declaration of the heapNode class, since it is used in the rbNode
// class.
class heapNode;

// Class representing a node in a red-black tree.
class rbNode {
private:
  rbNode *left, *right, *parent; // Pointers to the left child, right child, and
                                 // parent of the node.
  heapNode *heapNodeRef; // Pointer to the corresponding node in the heap.
  nodeColor color;       // Color of the node.

public:
  // Data values held by the node.
  int rideNumber, rideCost, tripDuration;

  // Static sentinel node to represent a null node in the tree.
  static rbNode NIL;

  // Constructor and destructor.
  rbNode(int rideNumber, int rideCost, int tripDuration);
  ~rbNode();

  // Getters and setters for private member variables.
  nodeColor getColor() const;
  void setColor(nodeColor newColor);

  heapNode *getHeapNodeRef() const;
  void setHeapNodeRef(heapNode *newHeapNodeRef);

  rbNode *getParent() const;
  void setParent(rbNode *newParent);

  rbNode *getLeft() const;
  void setLeft(rbNode *newLeft);

  rbNode *getRight() const;
  void setRight(rbNode *newRight);

  // Overloaded output operator to print out the node.
  friend std::ostream &operator<<(std::ostream &os, const rbNode &node);
};

#endif // RBNODE_H