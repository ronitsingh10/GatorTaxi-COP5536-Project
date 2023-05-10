#ifndef HEAPNODE_H
#define HEAPNODE_H

#include <iostream>

// Forward declaration of the rbNode class, since it is used in the heap Node
// class.
class rbNode;

class heapNode {
private:
  int rideNumber, rideCost, tripDuration; // Data values held by the node.
  rbNode *rbNodeRef; // A pointer to the corresponding red-black node in red
                     // black tree.
public:
  int pos = 0; // position of this heap node in heap array.

  // Constructor and destructor.
  heapNode(int rideNumber, int rideCost, int tripDuration);
  ~heapNode();

  // Less-than operator overload for heapNode class.
  // The comparison is first done on the basis of the ride cost and if the ride
  //  cost is the same, then it is done based on the trip duration.
  bool operator<(const heapNode &other) const;

  // Getter and setter for heap node reference.
  rbNode *getrbNodeRef() const;
  void setrbNodeRef(rbNode *newHeapNodeRef);

  // Overloaded output operator to print out the heap node.
  friend std::ostream &operator<<(std::ostream &os, const heapNode &node);
};

#endif // HEAPNODE_H