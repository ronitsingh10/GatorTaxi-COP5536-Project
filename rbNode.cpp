#include "rbNode.hpp"
#include "heapNode.hpp"

// Initialize the NIL node to have rideNumber, rideCost, and tripDuration of -1.
rbNode rbNode::NIL = rbNode(-1, -1, -1);

/**
 * @brief Constructor for rbNode class.
 *
 * @param rideNumber The ride number.
 * @param rideCost The cost of the ride.
 * @param tripDuration The duration of the trip.
 */
rbNode::rbNode(int rideNumber, int rideCost, int tripDuration)
    : rideNumber(rideNumber), rideCost(rideCost), tripDuration(tripDuration),
      heapNodeRef(nullptr) {
  setParent(&NIL);
  setLeft(&NIL);
  setRight(&NIL);

  setColor(rideNumber == -1 ? nodeColor::BLACK : nodeColor::RED);
}

/**
 *
 * @brief Destructor for rbNode class.
 */
rbNode::~rbNode() {}

/**
 * @brief Set the color of the node.
 *
 * @return nodeColor The color of the node.
 */
nodeColor rbNode::getColor() const {
  return color;
}

/**
 * @brief Get the color of the node.
 *
 * @param newColor The new color of the node.
 */
void rbNode::setColor(nodeColor newColor) {
  color = newColor;
}

/**
 * @brief  Get the heap Node Reference of the node.
 *
 * @return heapNode* Pointer to the heapNode associated with the red black Node.
 */
heapNode *rbNode::getHeapNodeRef() const {
  return heapNodeRef;
}

/**
 * @brief Set the heap Node Reference of the node.
 *
 * @param  newHeapNodeRef The new heapNode to associate with the red black Node.
 */
void rbNode::setHeapNodeRef(heapNode *newHeapNodeRef) {
  heapNodeRef = newHeapNodeRef;
}

/**
 * @brief  Get the parent of the node.
 *
 * @return rbNode* Pointer to the parent of the node.
 */
rbNode *rbNode::getParent() const {
  return parent;
}

/**
 * @brief Set the parent of the node.
 *
 * @param  newParent Pointer to the new parent node.
 */
void rbNode::setParent(rbNode *newParent) {
  parent = newParent;
}

/**
 * @brief Get the left child of the node.
 *
 * @return  rbNode* Pointer to the left child of the node.
 */
rbNode *rbNode::getLeft() const {
  return left;
}

/**
 * @brief Set the left child of the node.
 *
 * @param newLeft Pointer to the new left child node.
 */
void rbNode::setLeft(rbNode *newLeft) {
  left = newLeft;
}

/**
 * @brief Get the right child of the node.
 *
 * @return rbNode* Pointer to the right child of the node.
 */
rbNode *rbNode::getRight() const {
  return right;
}

/**
 * @brief Set the right child of the node.
 *
 * @param Set the right child of the node.
 */
void rbNode::setRight(rbNode *newRight) {
  right = newRight;
}

/**
 * @brief Overloaded stream insertion operator for red black tree node class.
 *
 * @param os The output stream.
 * @param node The red black tree node object to insert into the stream.
 * @return std::ostream& A reference to the output stream.
 */
std::ostream &operator<<(std::ostream &os, const rbNode &node) {
  os << '(' << node.rideNumber << "," << node.rideCost << ","
     << node.tripDuration << ')';
  return os;
}