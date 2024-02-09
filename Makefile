CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20

DEBUGGER = gdb

IXXFLAGS = -Iinclude -Ilib/raylib/src -Ilib/raygui/src
LDFLAGS = -Llib
LXXFLAGS = -lraylib -lm -ldl -lpthread -lGL 

SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, bin/%.obj, $(SRC))

TARGET := bin/Memo.out

.PHONY: all run clear

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LXXFLAGS)

$(OBJ): bin/%.obj: src/%.cpp
	@echo Compiling: $<
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(IXXFLAGS) 

run:
	@echo Running: $(TARGET)
	./$(TARGET)

clear:
	@echo Removing: $(OBJ)
	rm -rf $(OBJ)
	@echo Removing: $(TARGET)
	rm -rf $(TARGET)

debug:
	$(DEBUGGER) $(TARGET)