# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic-errors -Wno-reorder -Wno-sign-compare

# Target executable
TARGET = gatorTaxi

# Object files
OBJS = heapNode.o minHeap.o rbNode.o rbTree.o main.o

# Default rule
all: $(TARGET)

# Rule to create the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to create object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Include dependencies
-include $(OBJS:.o=.d)

# Rule to generate dependencies
%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MM -MT '$(patsubst %.cpp,%.o,$<)' $< -MF $@

# Clean rule
clean:
	rm -f $(OBJS) $(OBJS:.o=.d) $(TARGET)

.PHONY: all clean