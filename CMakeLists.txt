cmake_minimum_required(VERSION 3.9)
project(Sokoban)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

add_executable(Sokoban src/main.cpp src/Map.cpp src/Map.h src/State.cpp src/State.hpp)
