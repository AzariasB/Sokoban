cmake_minimum_required(VERSION 3.9)
project(Sokoban)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sokoban src/main.cpp src/Map.cpp src/Map.h src/TileMap.cpp src/TileMap.h src/Window.cpp src/Window.h)

set(SFML_ROOT "C:/SFML-2.4.2")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Sokoban ${SFML_LIBRARIES})
endif()
