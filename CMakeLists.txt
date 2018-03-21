cmake_minimum_required(VERSION 3.9)
project(Sokoban)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sokoban src/main.cpp src/Map.cpp src/Map.h)
