cmake_minimum_required(VERSION 3.19)
project(ClionProjects)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(ClionProjects main.cpp)

target_link_libraries(ClionProjects sfml-graphics sfml-audio)

configure_file(resources/arial.ttf resources/arial.ttf COPYONLY)
configure_file(resources/words.txt resources/words.txt COPYONLY)
