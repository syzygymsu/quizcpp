cmake_minimum_required(VERSION 3.19)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory("aa1")
add_subdirectory("aa2")
add_subdirectory("skype")
