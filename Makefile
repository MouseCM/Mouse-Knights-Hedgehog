SRC_DIR = .
BUILD_DIR = build/debug
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/main.cpp)
INCLUDE_PATHS = -I/opt/homebrew/opt/sdl2/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.8.5/include -I/opt/homebrew/Cellar/sdl2_mixer/2.8.1_1/include 
LIBRARY_PATHS = -L/opt/homebrew/opt/sdl2/lib -L/opt/homebrew/Cellar/sdl2_image/2.8.5/lib -L/opt/homebrew/Cellar/sdl2_mixer/2.8.1_1/lib
COMPILER_FLAGS = -std=c++11 -Wall -O0 -g
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer

all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o main