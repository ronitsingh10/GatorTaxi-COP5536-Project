#ifndef MINHEAP_H
#define MINHEAP_H

#include "heapNode.hpp"
#include <vector>

class minHeap {
private:
  // private helper functions

  // check if the heap is empty
  bool isEmpty();

  // get the index of the parent of a given node
  int getParent(int index);

  // get the index of the left child of a given node
  int getLeftChild(int index);

  // get the index of the right child of a given node
  int getRightChild(int index);

  // check if a given index is a valid index in the heap
  bool isValidIndex(int index);

  // swap the elements at two given indices in the heap
  void swap(int index1, int index2);

  // perform the "heapify up" operation at a given position in the heap
  void heapifyUp(int position);

  // perform the "heapify down" operation at a given position in the heap
  void heapifyDown(int position);

public:
  // public member variables
  // the underlying vector that stores the elements of the heap
  std::vector<heapNode> heap;
  // the current size of the heap (initialized to 1 because the root of the heap
  // is initially empty)
  int size = 1;

  // constructor and destructor
  minHeap();
  ~minHeap();

  // public member functions

  // get a pointer to the underlying vector that stores the elements of the heap
  heapNode *getAddress();

  // insert a new element into the heap
  void insert(heapNode node);

  // remove and return the minimum element from the heap
  heapNode removeMin();

  // remove the element at a given index from the heap
  void remove(int index);
};

#endif // MINHEAP_H