cmake_minimum_required(VERSION 3.0)

project(ghostgame)

set(CMAKE_CXX_COMPILER "/usr/bin/g++")

# Set the path to the SFML installation on your system
set(SFML_DIR "path/to/SFML/cmake/modules" CACHE PATH "SFML CMake module path")

# Find the SFML components
find_package(SFML COMPONENTS system window graphics REQUIRED)

# Add the executable and link against SFML
add_executable(ghostgame main.cpp game_window.cpp game_scene.cpp sprites.cpp level.cpp)
target_link_libraries(ghostgame PRIVATE sfml-system sfml-window sfml-graphics)

# Install the executable
install(TARGETS ghostgame RUNTIME DESTINATION bin)
