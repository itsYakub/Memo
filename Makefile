CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20

DEBUGGER = gdb

IXXFLAGS = -Iinclude -Ilib/libraylib -Ilib/raygui/src
LDFLAGS = -Llib/libraylib
LXXFLAGS = -lraylib -lm -ldl -lpthread -lGL 

SRC = $(wildcard src/*.cpp)

TARGET = bin/program.out

.PHONY: all run clear

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(IXXFLAGS) $(LDFLAGS) $^ -o $@ $(LXXFLAGS)

run:
	./$(TARGET)

clear:
	rm -rf $(TARGET)