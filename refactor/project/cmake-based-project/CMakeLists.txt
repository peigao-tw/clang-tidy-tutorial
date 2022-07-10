cmake_minimum_required(VERSION 3.0.0)

project(CMake_Based_Project VERSION 1.0.0)

add_subdirectory(miscellaneous)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE miscellaneous)
