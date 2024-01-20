CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++20

IXXFLAGS = -Iinclude -Ilib/raylib/lib
LDFLAGS = -Llib/raylib/lib
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