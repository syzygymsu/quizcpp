cmake_minimum_required(VERSION 3.19)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON)

add_subdirectory("anagrams")
add_subdirectory("exitOrFence")
add_subdirectory("LRU")
add_subdirectory("LRU_standart")
add_subdirectory("normalizePath")
add_subdirectory("urlify")
