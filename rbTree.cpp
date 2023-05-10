#include "rbTree.hpp"
#include <stdexcept>

/**
 * @brief Constructor for rbTree class
 * @details Initializes the nil and root pointers and sets the left and right
 * children of root to nil.
 */
rbTree::rbTree() {
  nil = &rbNode::NIL;
  root = nil;
  root->setLeft(nil);
  root->setRight(nil);
}

/**
 * @brief Destructor for rbTree class.
 */
rbTree::~rbTree() {}

/**
 * @brief Checks if a node is a left child of its parent.
 *
 * @param node The node to be checked.
 * @return true if node is a left child of its parent, false otherwise.
 */
bool rbTree::isLeftChild(rbNode *node) {
  return node == (node->getParent())->getLeft();
}

/**
 * @brief Checks if a node is a child child of its parent.
 *
 * @param node The node to be checked.
 * @return true if node is a right child of its parent, false otherwise.
 */
bool rbTree::isRightChild(rbNode *node) {
  return node == (node->getParent())->getRight();
}

/**
 * @brief Updates child link for parent node.
 *
 * @param parent The parent node to be updated.
 * @param oldChild The child node to be replaced.
 * @param newChild The new child node to be updated.
 **/
void rbTree::UpdateParentChildLink(rbNode *parent, rbNode *oldChild,
                                   rbNode *newChild) {
  // Set parent as new-child's parent.
  newChild->setParent(parent);

  if (parent == nil) { // If rotation caused the new child to become root.
    root = newChild;
  } else if (isLeftChild(oldChild)) { // If the old child was in the left.
    parent->setLeft(newChild);
  } else { // If the old child was in the right.
    parent->setRight(newChild);
  }
}

/**
 * @brief Performs a right rotation on the given node.
 *
 * @param node The node to be rotated right.
 **/
void rbTree::rotateRight(rbNode *node) {
  // Get the left child of the input node
  rbNode *Y_Node = node->getLeft();

  // Set the left child of the input node to the right child of Y_Node
  node->setLeft(Y_Node->getRight());

  // Set the input node as parent of Y_Node's right child, if it exists
  if (Y_Node->getRight() != nil) {
    (Y_Node->getRight())->setParent(node);
  }

  // Update the parent-child link between the input node's parent and Y_Node
  UpdateParentChildLink(node->getParent(), node, Y_Node);

  // Perform the right rotation
  Y_Node->setRight(node);
  node->setParent(Y_Node);
}

/**
 * @brief Performs a left rotation on the given node.
 *
 * @param node The node to be rotated left.
 **/
void rbTree::rotateLeft(rbNode *node) {
  // Get the right child of the input node
  rbNode *Y_Node = node->getRight();

  // Set the right child of the input node to the left child of Y_Node
  node->setRight(Y_Node->getLeft());

  // Set the input node as parent of Y_Node's left child, if it exists
  if (Y_Node->getLeft() != nil) {
    (Y_Node->getLeft())->setParent(node);
  }

  // Update the parent-child link between the input node's parent and Y_Node
  UpdateParentChildLink(node->getParent(), node, Y_Node);

  // Perform the left rotation
  Y_Node->setLeft(node);
  node->setParent(Y_Node);
}

/**
 * @brief Rebalances the Red-Black tree after insertion of a new node.
 *
 * @param node A pointer to the node that was inserted.
 */
void rbTree::insertionRebalance(rbNode *node) {
  rbNode *Y_Node = nullptr;

  // Loop until the parent of the input node is red
  while ((node->getParent())->getColor() == nodeColor::RED) {
    if (isLeftChild(node->getParent())) {
      // Get the right child of the grandparent of the input node
      Y_Node = ((node->getParent())->getParent())->getRight();

      if (Y_Node->getColor() == nodeColor::RED) {
        // Recolor the parent of the input node, Y_Node, and the grandparent of
        // the input node
        (node->getParent())->setColor(nodeColor::BLACK);
        Y_Node->setColor(nodeColor::BLACK);
        ((node->getParent())->getParent())->setColor(nodeColor::RED);

        // Move up the tree to the grandparent of the input node
        node = (node->getParent())->getParent();
      } else {
        // If the input node is a right child
        if (isRightChild(node)) {

          // Move up the tree to the parent of the input node
          node = node->getParent();
          rotateLeft(node);
        }

        // Recolor the parent of the input node and the grandparent of the input
        // node
        (node->getParent())->setColor(nodeColor::BLACK);
        ((node->getParent())->getParent())->setColor(nodeColor::RED);

        // Perform a right rotation on the grandparent of the input node
        rotateRight((node->getParent())->getParent());
      }
    } else {
      // Get the left child of the grandparent of the input node
      Y_Node = ((node->getParent())->getParent())->getLeft();

      if (Y_Node->getColor() == nodeColor::RED) {
        // Recolor the parent of the input node, Y_Node, and the grandparent of
        // the input node
        (node->getParent())->setColor(nodeColor::BLACK);
        Y_Node->setColor(nodeColor::BLACK);
        ((node->getParent())->getParent())->setColor(nodeColor::RED);

        // Move up the tree to the grandparent of the input node
        node = (node->getParent())->getParent();
      } else {
        if (isLeftChild(node)) {
          node = node->getParent();
          rotateRight(node);
        }

        // Recolor the parent of the input node and the grandparent of the input
        // node
        (node->getParent())->setColor(nodeColor::BLACK);
        (node->getParent())->getParent()->setColor(nodeColor::RED);

        // Perform a left rotation on the grandparent of the input node
        rotateLeft((node->getParent())->getParent());
      }
    }
  }

  // Set the color of the root node to black
  root->setColor(nodeColor::BLACK);
}

/**
 * @brief Inserts a new node into the tree and rebalances if necessary.
 *
 * @param node The node to be inserted into the tree.
 * @throw std::runtime_error If the key value already exists in the tree.
 **/
void rbTree::insert(rbNode *node) {
  if (node == nullptr) {
    throw std::runtime_error("The node isn't a valid node\n");
  }

  rbNode *X_Node = root, *Y_Node = nil;

  // finding the position where this node should be added in red black tree by
  // binary tree properties
  while (X_Node != nil) {
    Y_Node = X_Node;

    if (node->rideNumber < X_Node->rideNumber) {
      X_Node = X_Node->getLeft();
    } else if (node->rideNumber > X_Node->rideNumber) {
      X_Node = X_Node->getRight();
    } else {
      throw std::runtime_error("Duplicate RideNumber\n");
    }
  }

  node->setParent(Y_Node);

  // Inserts the node at appropriate position by binary tree properties.
  if (Y_Node == nil) {
    root = node;
  } else if (node->rideNumber < Y_Node->rideNumber) {
    Y_Node->setLeft(node);
  } else if (node->rideNumber > Y_Node->rideNumber) {
    Y_Node->setRight(node);
  } else if (node->rideNumber == Y_Node->rideNumber) {
    throw std::runtime_error("Duplicate RideNumber\n");
  }

  // Rebalancing the tree after insertion
  insertionRebalance(node);
}

/**
 * @brief Finds minimum node under the given node.
 *
 * @param node: The root node from which to find the minimum node.
 * @return The minimum node in the subtree rooted at node.
 **/
rbNode *rbTree::getMinimumNode(rbNode *node) {
  while (node->getLeft() != nil) {
    node = node->getLeft();
  }
  return node;
}

/**
 * @brief Rebalances the tree after a node deletion.
 *
 * @param node the node that was deleted.
 */
void rbTree::DeletionRebalance(rbNode *node) {
  while (node != root && node->getColor() == nodeColor::BLACK) {
    rbNode *sibling;
    if (isLeftChild(node)) {
      // Get the sibling of the node
      sibling = (node->getParent())->getRight();

      if (sibling->getColor() == nodeColor::RED) { // Case 1: sibling is red
        sibling->setColor(
            nodeColor::BLACK); // Set the color of the sibling to black
        (node->getParent())
            ->setColor(nodeColor::RED); // Set the color of the parent to red
        rotateLeft(node->getParent());  // Rotate left at the parent
        sibling = (node->getParent())->getRight(); // Get the new sibling
      }

      if ((sibling->getLeft())->getColor() == nodeColor::BLACK &&
          (sibling->getRight())->getColor() ==
              nodeColor::BLACK) { // Case 2: both children of sibling are black
        sibling->setColor(
            nodeColor::RED);      // Set the color of the sibling to red
        node = node->getParent(); // Move up to the parent
      } else { // Case 3: at least one child of sibling is red
        if ((sibling->getRight())->getColor() ==
            nodeColor::BLACK) { // Subcase 3.1: right child of sibling is black
          (sibling->getLeft())
              ->setColor(nodeColor::BLACK); // Set the color of the left child
                                            // of sibling to black
          sibling->setColor(
              nodeColor::RED);  // Set the color of the sibling to red
          rotateRight(sibling); // Rotate right at the sibling
          sibling = (node->getParent())->getRight(); // Get the new sibling
        }

        sibling->setColor(
            (node->getParent())->getColor()); // Set the color of the sibling to
                                              // the color of the parent
        (node->getParent())
            ->setColor(
                nodeColor::BLACK); // Set the color of the parent to black
        (sibling->getRight())
            ->setColor(nodeColor::BLACK); // Set the color of the right child of
                                          // sibling to black
        rotateLeft(node->getParent());    // Rotate left at the parent
        node = root;
      }
    } else { // Same as above, but for right child
      sibling = (node->getParent())->getLeft();
      if (sibling->getColor() == nodeColor::RED) {
        sibling->setColor(nodeColor::BLACK);
        (node->getParent())->setColor(nodeColor::RED);
        rotateRight(node->getParent());
        sibling = (node->getParent())->getLeft();
      }

      if ((sibling->getRight())->getColor() == nodeColor::BLACK &&
          (sibling->getLeft())->getColor() == nodeColor::BLACK) {
        sibling->setColor(nodeColor::RED);
        node = node->getParent();
      } else {
        if ((sibling->getLeft())->getColor() == nodeColor::BLACK) {
          (sibling->getRight())->setColor(nodeColor::BLACK);
          sibling->setColor(nodeColor::RED);
          rotateLeft(sibling);
          sibling = (node->getParent())->getLeft();
        }

        sibling->setColor((node->getParent())->getColor());
        (node->getParent())->setColor(nodeColor::BLACK);
        (sibling->getLeft())->setColor(nodeColor::BLACK);
        rotateRight(node->getParent());
        node = root;
      }
    }
  }

  node->setColor(nodeColor::BLACK);
}

/**
 * @brief Delete a node from the tree.
 * Given a node pointer, this function deletes the node from the red-black tree.
 * It first checks if the given node is valid or not, and then it deletes the
 * node by either replacing it with its right child or left child or minimum
 * node from the right subtree of the node. After deleting the node, it
 * rebalances the tree by calling DeletionRebalance function.
 *
 * @param node Pointer to the node to be deleted.
 * @throws std::runtime_error if the node is not a valid node.
 */
void rbTree::deleteNode(rbNode *node) {
  if (node == nullptr) {
    throw std::runtime_error("The node isn't a valid node\n");
  }

  rbNode *X_Node = nullptr, *Y_Node = node;
  nodeColor NodeColor = Y_Node->getColor();

  if (node->getLeft() ==
      nil) { // Handle case when the node has only right child or no child
    X_Node = node->getRight();
    UpdateParentChildLink(node->getParent(), node,
                          node->getRight()); // Update parent's child link
  } else if (node->getRight() == nil) {
    X_Node = node->getLeft();
    UpdateParentChildLink(node->getParent(), node, node->getLeft());
  } else { // Handle case when the node has both left and right child
    Y_Node = getMinimumNode(node->getRight());
    NodeColor = Y_Node->getColor();

    X_Node = Y_Node->getRight();

    if (Y_Node->getParent() == node) { // If minimum node is node's right child
      X_Node->setParent(Y_Node);
    } else {
      UpdateParentChildLink(Y_Node->getParent(), Y_Node, Y_Node->getRight());
      Y_Node->setRight(node->getRight());
      (Y_Node->getRight())->setParent(Y_Node);
    }

    UpdateParentChildLink(node->getParent(), node, Y_Node);
    Y_Node->setLeft(node->getLeft());
    (Y_Node->getLeft())->setParent(Y_Node);
    Y_Node->setColor(node->getColor()); // Set minimum node's color same as that
                                        // of node being deleted
  }

  if (NodeColor == nodeColor::BLACK) {
    DeletionRebalance(X_Node);
  }
}

/**
 * @brief Recursive search for a node with a given ride number.
 * Given the root node and a ride number, this function recursively searches the
 * red-black tree for the node with the given ride number. It returns the node
 * pointer if it is found, otherwise it returns nullptr.
 *
 * @param root Pointer to the root node of the tree.
 * @param rideNumber The ride number to be searched.
 * @return Pointer to the node with the given ride number if it is found,
 * otherwise nullptr.
 */
rbNode *rbTree::searchRecursive(rbNode *root, int rideNumber) {
  if (root == nil) {
    return nullptr;
  }

  if (root->rideNumber == rideNumber) { // if node found then return
    return root;
  } else if (root->rideNumber >
             rideNumber) { // if root' ridenumber is greater than given
                           // ridenumber then look in left side
    return searchRecursive(root->getLeft(), rideNumber);
  } else { // if root' ridenumber is lesser than given
           // ridenumber then look in right side
    return searchRecursive(root->getRight(), rideNumber);
  }
}

/**
 * @brief Search for a node with a given ride number.
 * Given a ride number, this function searches the red-black tree for the node
 * with the given ride number by calling searchRecursive function. It returns
 * the node pointer if it is found, otherwise it returns nullptr.
 *
 * @param rideNumber The ride number to be searched.
 * @return Pointer to the node with the given ride number if it is found,
 * otherwise nullptr.
 */
rbNode *rbTree::search(int rideNumber) {
  return searchRecursive(root, rideNumber);
}

/**
 * @brief Recursive search for nodes within a given range.
 * Given the root node, two ride numbers, and a vector to store the nodes, this
 * function recursively searches the red-black tree for the nodes with the ride
 * numbers within the given range. It adds the nodes found within the range to
 * the vector passed by reference. This function is called by searchInRange
 * function.
 *
 * @param root Pointer to the root node of the tree.
 * @param rideNumber1 The lower bound of the range of ride numbers to be
 * searched.
 * @param rideNumber2 The upper bound of the range of ride numbers to be
 * searched.
 * @param vec A vector to store the nodes found within the range.
 */
void rbTree::searchInRangeRecursive(rbNode *root, int rideNumber1,
                                    int rideNumber2, std::vector<rbNode> &vec) {
  if (root == nil) {
    return;
  }

  if (root->rideNumber > rideNumber1) {
    // if root's ridenumber is greater than given
    // ridenumber then look in left side
    searchInRangeRecursive(root->getLeft(), rideNumber1, rideNumber2, vec);
  }

  if (root->rideNumber >= rideNumber1 && root->rideNumber <= rideNumber2) {
    // if found then insert in vector of rbNode pointers
    rbNode inRangeNode = *root;
    vec.push_back(inRangeNode);
  }

  if (root->rideNumber < rideNumber2) {
    // if root's ridenumber is lesser than given
    // ridenumber then look in right side
    searchInRangeRecursive(root->getRight(), rideNumber1, rideNumber2, vec);
  }
}

/**
* @brief Search for nodes within a given range.
* Given two ride numbers, this function searches the red-black tree for the
* nodes with the ride numbers within the
* given range by calling searchInRangeRecursive function. It returns a vector
containing the nodes found within the
* range.
*
* @param rideNumber1 The lower bound of the range of ride numbers to be
* searched.
* @param rideNumber2 The upper bound of the range of ride numbers to be
* searched.
* @return A vector containing the nodes with the ride numbers within the given
* range.
*/
std::vector<rbNode> rbTree::searchInRange(int rideNumber1, int rideNumber2) {
  std::vector<rbNode> res;
  searchInRangeRecursive(root, rideNumber1, rideNumber2, res);
  return res;
}