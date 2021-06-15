cmake_minimum_required(VERSION 3.19)
project(ClionProjects)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(ClionProjects main.cpp)

target_link_libraries(ClionProjects sfml-graphics sfml-audio)
