cmake_minimum_required(VERSION 3.0)

project(ghostgame)

add_executable(ghostgame main.cpp)

install(TARGETS ghostgame RUNTIME DESTINATION bin)
