cmake_minimum_required(VERSION 3.15)
project(_clionProjectToDoOffline)

set(CMAKE_CXX_STANDARD 20)


add_executable(GraphAdjList "offline_and_reports/Offline-1- Assignment_on_Graph/GraphAdjList.cpp")
add_executable(GraphAdjMatrix "offline_and_reports/Offline-1- Assignment_on_Graph/GraphAdjMatrix.cpp")
add_executable(dnf "offline_and_reports/Offline-2- Assignment_on_SSSP/dnf.cpp")
add_executable(apsp offline_and_reports/Offline-3-Assignment_on_APSP/apsp.cpp)
add_executable(mst offline_and_reports/Offline-4-Assignment_on_MST/mst.cpp)