# ===============================================================================
# Made by: Yakub (https://github.com/itsYakub)
# Version: 1.0.0
# ===============================================================================
#
# ===============================================================================
# Build mode (BUILD_MODE):
# > debug (default)
# > release
# ===============================================================================
# Build platform (BUILD_PLATFORM):
# > windows (default)
# > linux
# ===============================================================================
# Project's Licence:
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
# OR OTHER DEALINGS IN THE SOFTWARE.
# ===============================================================================
BUILD_PLATFORM ?= windows
BUILD_MODE ?= debug

ifeq ($(BUILD_MODE), debug)
	BUILD_DIR = bin
endif
ifeq ($(BUILD_MODE), release) 
	BUILD_DIR = game
endif

# Compiler used by the project
CXX = g++

# Default compilation flags
CXXFLAGS = -std=c++20

ifeq ($(BUILD_MODE), debug)
	CXXFLAGS += -g -Wall -Wextra
endif
ifeq ($(BUILD_MODE), release) 
	CXXFLAGS += -s -O2
endif

# Project's source files
SRCS = $(wildcard src/*.cpp)

# Project's include directories
# Make sure to provide the valid paths to the raylib's and raygui's include directories
IXXFLAGS = -Iinclude -Ilib/raylib/src -Ilib/raygui/src 

# Project's library directories
# Make sure to provide the valid path to the project's libraries
LDFLAGS = -Llib

# Project's libraries
# Make sure to compile the raylib to the STATIC library before running
# Doing otherwise will cause an error
ifeq ($(BUILD_PLATFORM), windows)
	LXXFLAGS = -lraylib -lgdi32 -lwinmm -lopengl32
endif
ifeq ($(BUILD_PLATFORM), linux) 
	LXXFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

# Project's binary files (.obj)
OBJS = $(patsubst src/%.cpp, $(BUILD_DIR)/%.obj, $(SRCS))

TARGET = $(BUILD_DIR)/Game.out

.PHONY: dirs build

all: dirs build

dirs:
ifeq ($(BUILD_MODE), debug)
	if [ ! -d "./bin" ]; then mkdir bin; fi
endif
ifeq ($(BUILD_MODE), release) 
	if [ ! -d "./game" ]; then mkdir game; fi
endif

build: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LXXFLAGS) 

ifeq ($(BUILD_MODE), release) 
	cp -r ./res ./$(BUILD_DIR)
	rm -rf $(OBJS)
endif

$(OBJS): $(BUILD_DIR)/%.obj: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(IXXFLAGS)

run:
	./$(TARGET)