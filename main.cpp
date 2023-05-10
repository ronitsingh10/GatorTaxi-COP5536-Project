#include "minHeap.hpp"
#include "rbTree.hpp"
#include <fstream>
#include <iostream>
#include <string>

minHeap myHeap;
rbTree myTree;

/**
* @brief This function inserts the ride information into both the red black tree
* and minheap.
*
* @param ridenumber, rideCost, tripDuration the ride information to be inserted
* @param out The output file stream object to output if duplicate ridenumber is
inserted
*/
void Insert(int rideNumber, int rideCost, int tripDuration,
            std::ofstream &out) {
  // Create a new red-black tree node with the given ride number, cost, and
  // duration.
  rbNode *rbnode = new rbNode(rideNumber, rideCost, tripDuration);
  // Create a new heap node with the given ride number, cost, and duration.
  heapNode heapnode = heapNode(rideNumber, rideCost, tripDuration);

  try {
    // Insert the new red-black tree node into the red-black tree.
    myTree.insert(rbnode);

    // Get the address of the new heap node in the heap.
    heapNode *adr = myHeap.getAddress();

    // Set the heap node reference of the red-black tree node to the address
    // obtained above.
    rbnode->setHeapNodeRef(adr);
    // Set the red-black tree node reference of the heap node to the new
    // red-black tree node.
    heapnode.setrbNodeRef(rbnode);

    // Insert the new heap node into the heap.
    myHeap.insert(heapnode);
  } catch (const std::exception &err) {
    // If an exception is thrown during the insertion due to duplicate
    // ridenNumber, print out the error message using the ofstream object.
    out << err.what() << std::endl;
    // Exit the program.
    exit(1);
  }
}

/**
This function retrieves the next ride from a heap data structure, deletes it
from the red black tree as well as the heap, and writes it to an output file
stream object.
@param out The output file stream object to which the next ride will be written.
*/
void GetNextRide(std::ofstream &out) {
  try {
    // Remove the minimum heap node from the heap.
    heapNode nextRide = myHeap.removeMin();
    myTree.deleteNode(nextRide.getrbNodeRef());
    out << nextRide << std::endl;
  } catch (const std::exception &err) {
    out << err.what() << std::endl;
  }
}

/**
 * @brief Prints the details of the ride with given rideNumber
 *
 * @param rideNumber The ride number to be printed
 * @param out The output stream to print the details to
 * If the ride is not found, "(0,0,0)" is printed.
 */
void Print(int rideNumber, std::ofstream &out) {
  rbNode *ride =
      myTree.search(rideNumber); // Search for ridenumber node in red black tree

  // if node not exist then write (0,0,0) otherwise the found ride
  if (ride == nullptr) {
    out << "(0,0,0)" << std::endl;
  } else {
    out << *ride << std::endl;
  }
}

/**
 * @brief Prints the details of all rides with ride numbers in the given range
 *
 * @param rideNumber1 The start ride number of the range (inclusive)
 * @param rideNumber2 The end ride number of the range (inclusive)
 * @param out The output stream to print the details to
 * If no rides are found in the range, "(0,0,0)" is printed.
 */
void Print(int rideNumber1, int rideNumer2, std::ofstream &out) {
  std::vector<rbNode> res = myTree.searchInRange(
      rideNumber1,
      rideNumer2); // Search for ride nodes in red black tree within range

  // if nodes do not exist then write (0,0,0) otherwise the found rides
  if (res.empty()) {
    out << "(0,0,0)" << std::endl;
  } else {
    for (int i = 0; i < res.size(); i++) {
      out << res[i] << ", "[i == res.size() - 1];
    }
    out << std::endl;
  }
}

/**
 * @brief Cancels the ride with given ride number
 *
 * @param rideNumber The ride number to be cancelled
 * Removes the ride from the red-black tree and the heap.
 */
void CancelRide(int rideNumber) {
  rbNode *ride = myTree.search(
      rideNumber); // Search for node with the ridenumber in red black tree

  // check if node exist
  if (ride != nullptr) {
    int idx = ride->getHeapNodeRef()->pos;
    myTree.deleteNode(ride); // Delete node from red black tree
    myHeap.remove(idx);      // Delete node from heap
  }
}

/**
 * @brief Updates the trip duration of a ride if the new duration is not more
 * than twice the current duration
 *
 * @param rideNumber The ride number of the ride to be updated
 * @param newTripDuration The new trip duration to be updated to
 * Removes the ride from the red-black tree and the heap, and reinserts the ride
 * with updated duration If the new trip duration is less than or equal to the
 * current duration, rideCost remains the same. If the new trip duration is more
 * than the current duration and less than twice its current duration, rideCost
 * increases by 10.
 */
void UpdateTrip(int rideNumber, int newTripDuration) {
  rbNode *ride = myTree.search(rideNumber);
  if (ride != nullptr) {
    // Remove ride from both the red black tree and min heap.
    int idx = ride->getHeapNodeRef()->pos;
    myTree.deleteNode(ride);
    myHeap.remove(idx);

    // if new trip duration is lesser than twice of previous tripduration then
    // insert new ride
    int currTripDuration = ride->tripDuration;
    if (newTripDuration <= 2 * currTripDuration) {
      // find ridecost for new ride, it will be same if then no change otherwise
      // add 10 to previous value
      int rideCost =
          ride->rideCost + (newTripDuration <= currTripDuration ? 0 : 10);
      rbNode *rbnode = new rbNode(rideNumber, rideCost, newTripDuration);
      heapNode heapnode = heapNode(rideNumber, rideCost, newTripDuration);

      myTree.insert(rbnode); // Insert into the red black tree.

      heapNode *adr = myHeap.getAddress(); // Get the address of the new heap
                                           // node in the heap.

      rbnode->setHeapNodeRef(adr);   // Set the heap node reference of the
                                     // red-black tree node to the address
                                     // obtained above.
      heapnode.setrbNodeRef(rbnode); // Set the red-black tree node reference of
                                     // the heap node to the new
                                     // red-black tree node.
      myHeap.insert(heapnode);       // Insert the new heap node into the heap.
    }
  }
}

/**
 * @brief A utility function to separate information from given string.
 *
 * @param s The string to be processes.
 */
std::vector<std::string> process_string(std::string s) {
  std::vector<std::string> vec = {""};
  for (char &c : s) {
    if (c == '(' || c == ',' || c == ')') {
      vec.emplace_back("");
    } else {
      vec.back() += c;
    }
  }
  vec.pop_back();
  return vec;
}

/**
 * @brief Main function that reads input commands from a file and executes them
 *
 * @param argc the number of arguments passed to the program
 * @param argv array of pointers to strings containing the arguments passed to
 * the program
 * @return 0 if the program exits successfully, 1 otherwise
 */
int main(int argc, char *argv[]) {
  // Check that the program is called with an input file argument
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " input_file_name\n";
    return 1;
  }

  // Open the input file for reading
  std::ifstream inFile(argv[1]);
  if (!inFile) {
    // Print an error message if the input file cannot be opened
    std::cout << "Error: could not open file " << argv[1] << std::endl;
    return 1;
  }

  // Open the output file for writing
  std::ofstream outFile("output_file.txt");
  if (!outFile) {
    // Print an error message if the output file cannot be opened
    std::cout << "Error: could not open file " << argv[1] << std::endl;
    return 1;
  }

  // Read from file line by line.
  std::string data;
  while (std::getline(inFile, data)) {
    // Split the input line into a vector of strings
    std::vector<std::string> command = process_string(data);

    // Determine which command to execute based on the first word in the
    // vector
    if (command.front() == "Insert") {
      Insert(std::stoi(command[1]), std::stoi(command[2]),
             std::stoi(command[3]), outFile);
    } else if (command.front() == "GetNextRide") {
      GetNextRide(outFile);
    } else if (command.front() == "Print") {
      if (command.size() == 2) {
        Print(std::stoi(command[1]), outFile);
      } else {
        Print(std::stoi(command[1]), std::stoi(command[2]), outFile);
      }
    } else if (command.front() == "UpdateTrip") {
      UpdateTrip(std::stoi(command[1]), std::stoi(command[2]));
    } else if (command.front() == "CancelRide") {
      CancelRide(std::stoi(command[1]));
    }
  }

  // Close the input and output files
  inFile.close();
  outFile.close();

  return 0;
}