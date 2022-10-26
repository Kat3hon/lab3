cmake_minimum_required(VERSION 3.21)
project(lab3)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE main.cpp board.cpp clamps_processing.cpp help.cpp)

add_compile_definitions(dynamic)
include_directories(external)
add_subdirectory(external)

add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} logicalElement_lib)

add_subdirectory(GTESTS)