cmake_minimum_required(VERSION 3.10)
project(Planner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/includes)

# Adding Source Files
file(GLOB SOURCES
     "src/core/**/*.cpp"
     "src/core/*.cpp"
)

# Adding libraries
# the paths were added manually because pkg-config was not able to find them
include_directories(/usr/local/Cellar/libpqxx/7.9.0/include)
link_directories(/usr/local/Cellar/libpqxx/7.9.0/lib)


add_executable(Planner ${SOURCES})

