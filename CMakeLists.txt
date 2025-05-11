cmake_minimum_required(VERSION 3.10)

# Define the project
project(Planner)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(
     ${PROJECT_SOURCE_DIR}/src
     ${PROJECT_SOURCE_DIR}/src/core
     ${PROJECT_SOURCE_DIR}/src/core/entities
     ${PROJECT_SOURCE_DIR}/src/core/interfaces
     ${PROJECT_SOURCE_DIR}/src/core/usecases
     ${PROJECT_SOURCE_DIR}/src/infrastructure
     ${PROJECT_SOURCE_DIR}/src/infrastructure/connection
     ${PROJECT_SOURCE_DIR}/src/infrastructure/reporitories/task-repository
     ${PROJECT_SOURCE_DIR}/src/ui
     ${PROJECT_SOURCE_DIR}/src/utils
)

# Add all source files recursively, ignoring core_1
file(GLOB_RECURSE SOURCES
    "src/core/*.cpp"
    "src/infrastructure/*.cpp"
    "src/ui/*.cpp"
    "src/utils/*.cpp"
    "src/*.cpp"
)

# Find the libpqxx library
find_package(libpqxx REQUIRED)

# Define the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link with libpqxx
target_link_libraries(${PROJECT_NAME} PRIVATE libpqxx::pqxx)
