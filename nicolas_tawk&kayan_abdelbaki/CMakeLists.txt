cmake_minimum_required(VERSION 3.28)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(main src/main.cpp  src/Graph.cpp src/User.cpp)
add_executable(graph src/Graph.cpp)
