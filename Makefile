CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20

DEBUGGER = gdb

IXXFLAGS = -Iinclude -Ilib/libraylib -Ilib/raygui/src
LDFLAGS = -Llib/libraylib
LXXFLAGS = -lraylib -lm -ldl -lpthread -lGL 

SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, bin/%.obj, $(SRC))

TARGET = bin/program.out

.PHONY: all run clear

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LXXFLAGS)

$(OBJ): bin/%.obj: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(IXXFLAGS) 

run:
	./$(TARGET)

clear:
	rm -rf $(OBJ)
	rm -rf $(TARGET)