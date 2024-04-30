cmake_minimum_required(VERSION 3.10)

# Define the project
project(Planner)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/includes)

# Adding Source Files
file(GLOB SOURCES
     "src/core/**/*.cpp"
     "src/database/**/*.cpp"
     "src/core/*.cpp"
)

find_package(libpqxx REQUIRED)

# Define the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link with libraries provided by Conan
# target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE libpqxx::pqxx)
