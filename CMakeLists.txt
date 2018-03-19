cmake_minimum_required(VERSION 3.6)
project(K_Map)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Term.cpp Term.h Variable.cpp Variable.h Kmap.cpp Kmap.h)
add_executable(K_Map ${SOURCE_FILES})