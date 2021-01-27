cmake_minimum_required(VERSION 3.16)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON)

set(SOURCE_HIRSH hirsh.cpp)
set(HEADERS_HIRSH hirsh.h)
set(SOURCE_TESTS test.cpp)
set(HEADERS_TESTS test.h)

add_library(hirsh ${SOURCE_HIRSH} ${HEADERS_HIRSH})
add_library(tests ${SOURCE_TESTS} ${HEADERS_TESTS})

add_executable(${ProjectId} main.cpp)
target_link_libraries(${ProjectId} hirsh tests)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${ProjectId})
