
## Makefile

```makefile
# Makefile for GridPath-Optimizer-3D

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = gridpath3d
SRC = main.cpp

# Default target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Verbose build
debug:
	$(CXX) -std=c++11 -Wall -Wextra -g -o $(TARGET) $(SRC)

# Clean
clean:
	rm -f $(TARGET) *.o

# Run with sample
run: $(TARGET)
	./$(TARGET) sample.txt

# Verbose run
run-v: $(TARGET)
	./$(TARGET) sample.txt -v

# Help
help:
	@echo "GridPath-Optimizer-3D Makefile"
	@echo ""
	@echo "  make          - Build gridpath3d"
	@echo "  make debug    - Build with debug symbols"
	@echo "  make clean    - Remove binary"
	@echo "  make run      - Build and run with sample.txt"
	@echo "  make run-v    - Build and run verbose mode"
	@echo "  make help     - Show this message"

.PHONY: all debug clean run run-v help
