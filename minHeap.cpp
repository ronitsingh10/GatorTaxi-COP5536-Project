#include "minHeap.hpp"
#include "rbNode.hpp"
#include <stdexcept>

/**
 * @brief Constructor for the min-heap.
 *
 * @details Initializes the heap vector with an initial capacity of 2005 and
 * sets the first element to a dummy node.
 */
minHeap::minHeap() {
  heap.reserve(2005);
  heap.front() = heapNode(-1, -1, -1);
}

/**
 * @brief Destructor for the min-heap.
 *
 * @details Does not perform any special cleanup because the heap vector is
 * destroyed automatically when the object is destroyed.
 */
minHeap::~minHeap() {}

/**
 * @brief Checks if the min-heap is empty.
 *
 * @return True if the heap contains no elements, false otherwise.
 */
bool minHeap::isEmpty() {
  return size <= 1;
}

/**
 * @brief Calculates the index of the parent of a given index in a min-heap.
 *
 * @param index The index of the child node.
 * @return The index of the parent node.
 */
int minHeap::getParent(int index) {
  return index / 2;
}

/**
 * @brief Calculates the index of the left child of a given index in the
 * min-heap.
 *
 * @param index The index of the parent node.
 * @return The index of the left child node.
 */
int minHeap::getLeftChild(int index) {
  return 2 * index;
}

/**
 * @brief Calculates the index of the right child of a given index in the
 * min-heap.
 *
 * @param index The index of the parent node.
 * @return The index of the right child node.
 */
int minHeap::getRightChild(int index) {
  return 2 * index + 1;
}

/**
 * @brief Checks if a given index is valid for the current heap.
 *
 * @param index The index to check.
 * @return True if the index is valid, false otherwise.
 */
bool minHeap::isValidIndex(int index) {
  return index >= 1 && index < size;
}

/**
 * @brief Swaps the positions of two nodes in the heap and updates their
 * references in the red black tree.
 *
 * @param index1 The index of the first node.
 * @param index2 The index of the second node.
 */
void minHeap::swap(int index1, int index2) {
  // Find red black node reference for both indexes.
  rbNode *rb1 = heap[index1].getrbNodeRef();
  rbNode *rb2 = heap[index2].getrbNodeRef();

  // Interchange the red black tree reference
  rb1->setHeapNodeRef(&heap[index2]);
  rb2->setHeapNodeRef(&heap[index1]);

  // Create a temporary heap node to be used to swap nodes.
  heapNode temp = heap[index1];

  heap[index1] = heap[index2];
  heap[index2] = temp;

  // Change the pos of both nodes to newer indexes.
  heap[index1].pos = index1;
  heap[index2].pos = index2;
}

/**
 * @brief Restores the min-heap property by recursively swapping a node with its
 * parent until the heap property is restored.
 *
 * @param position The index of the node to heapify up from.
 */
void minHeap::heapifyUp(int position) {
  if (heap[position] < heap[getParent(position)]) {
    swap(position, getParent(position)); // Swap nodes of current position with
                                         // parent if parent is greater
    heapifyUp(getParent(position));
  }
}

/**
 * @brief Inserts a new node into the min-heap and restores the heap property
 * @param node The node to insert into the heap.
 */
void minHeap::insert(heapNode node) {
  heap[size] = node;
  heap[size].pos = size;
  heapifyUp(size);
  size++;
}

/**
 * @brief Restores the heap property by heapifying down from the given position.
 *
 * @param position The index of the element to start the heapify-down process
 * from.
 */
void minHeap::heapifyDown(int position) {
  // Check if a valid left child node exists.
  if (isValidIndex(getLeftChild(position))) {
    int leftChild = getLeftChild(position);

    // Check if a valid right child node exists, otherwise assign the left child
    // index.
    int rightChild = isValidIndex(getRightChild(position))
                         ? getRightChild(position)
                         : leftChild;

    // Determine the minimum value child node.
    int minChild = heap[leftChild] < heap[rightChild] ? leftChild : rightChild;

    // If the value of the minimum child node is less than the current node,
    // swap them.
    if (heap[minChild] < heap[position]) {
      swap(position, minChild);
      // Recursively call heapifyDown on the minimum child node to continue the
      // heapification process.
      heapifyDown(minChild);
    }
  }
}

/**
 * @brief Removes and returns the minimum element from the heap.
 *
 * @return The minimum element in the heap.
 * @throws std::runtime_error If the heap is empty.
 */
heapNode minHeap::removeMin() {
  if (isEmpty()) {
    throw std::runtime_error("No active ride requests");
  }

  // Get the minimum element & Swap the minimum element with the last element
  heapNode minNode = heap[1];
  swap(1, size - 1);

  size--; // Decrease the size of the heap

  // Heapify down to maintain heap property
  heapifyDown(1);
  return minNode;
}

/**
 * @brief Removes the element at the specified index from the heap.
 *
 * @param index The index of the element to be removed.
 */
void minHeap::remove(int index) {
  swap(index,
       size - 1);     // swap the elements on last index and the required index
  size--;             // Decrease the size of the heap
  heapifyDown(index); // Heapify down from the index to maintain heap property
}

/**
 * @brief Returns a pointer to the next available memory address in the heap.
 *
 * @return A pointer to the next available memory address in the heap.
 */
heapNode *minHeap::getAddress() {
  return &heap[size];
}