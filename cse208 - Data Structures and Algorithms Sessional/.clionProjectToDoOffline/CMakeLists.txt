cmake_minimum_required(VERSION 3.15)
project(_clionProjectToDoOffline)

set(CMAKE_CXX_STANDARD 20)

add_executable(_clionProjectToDoOffline main.cpp)
add_executable(graphOffline offlines/offline-1/GraphAdjMatrix.cpp)
add_executable(GraphAdjList offlines/offline-1/GraphAdjList.cpp)