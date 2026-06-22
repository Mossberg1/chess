.PHONY: all configure build run clean

# Default target when you just type 'make'
all: build

# 1. Generate the CMake build files into a 'build' directory
configure:
	cmake -S . -B build

# 2. Compile the project using the generated CMake files
build: configure
	cmake --build build

# 3. Build the project and immediately run it
run: build
	./build/chess

# 4. Delete the build folder to start totally fresh
clean:
	rm -rf build