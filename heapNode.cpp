#include "heapNode.hpp"
#include "rbNode.hpp"

/**
 * @brief Constructor for heapNode class.
 *
 * @param rideNumber The ride number.
 * @param rideCost The ride cost.
 * @param tripDuration The trip duration.
 * @param rbNodeRef Pointer to a red-black tree node reference.
 */
heapNode::heapNode(int rideNumber, int rideCost, int tripDuration)
    : rideNumber(rideNumber), rideCost(rideCost), tripDuration(tripDuration),
      rbNodeRef(nullptr) {}

/**
 * @brief Destructor for heapNode class.
 */
heapNode::~heapNode() {}

/**
 * @brief Comparison operator for heapNode class.
 *
 * @param other The other heapNode to compare against.
 * @return True if this heapNode is less than the other heapNode, false
 * otherwise.
 */
bool heapNode::operator<(const heapNode &other) const {
  if (rideCost == other.rideCost) {
    return tripDuration < other.tripDuration;
  }
  return rideCost < other.rideCost;
}

/**
 * @brief Getter for the red-black tree node reference.
 *
 * @return A pointer to the red-black tree node reference.
 */
rbNode *heapNode::getrbNodeRef() const {
  return rbNodeRef;
}

/**
 * @brief Setter for the red-black tree node reference.
 *
 * @param newHeapNodeRef Pointer to a red-black tree node reference.
 */
void heapNode::setrbNodeRef(rbNode *newHeapNodeRef) {
  rbNodeRef = newHeapNodeRef;
}

/**
 * @brief Overloaded stream insertion operator for heapNode class.
 *
 * @param os The output stream.
 * @param node The heapNode object to insert into the stream.
 * @return A reference to the output stream.
 */
std::ostream &operator<<(std::ostream &os, const heapNode &node) {
  os << '(' << node.rideNumber << "," << node.rideCost << ","
     << node.tripDuration << ')';
  return os;
}