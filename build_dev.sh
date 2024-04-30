#!/bin/bash

# Create the build directory if it does not exist
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

# Clean the contents of the build directory
echo "Cleaning build directory..."
rm -rf ./build/*

# Detect the Conan profile only if no default profile exists
if [ -z "$(conan profile list | grep default)" ]; then
    echo "Detecting Conan profile..."
    conan profile detect
fi

# Install dependencies with Conan
echo "Installing dependencies with Conan..."
conan install . --output-folder=build --build=missing

# Move to the build directory
cd build

# Configure CMake
echo "Configuring CMake..."
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release

# # Reconfigure CMake to be safe
# cmake ..

# Build the project
echo "Building project..."
make

# Return to the root directory
cd ..
