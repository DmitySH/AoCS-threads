cmake_minimum_required(VERSION 3.16)
project(Task5)

set(CMAKE_CXX_STANDARD 17)

add_executable(Task5 main.cpp
        entities/PirateGang.cpp
        entities/PirateGang.h
        entities/Island.cpp
        entities/Island.h)

find_package (Threads)
target_link_libraries (Task5 ${CMAKE_THREAD_LIBS_INIT})
set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all"
        CACHE STRING "Compiler flags in asan build"
        FORCE)
