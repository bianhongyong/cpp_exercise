cmake_minimum_required(VERSION 3.0)
project(MyProject)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} main.cpp tree.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})