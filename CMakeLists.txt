cmake_minimum_required(VERSION 3.15)
project(ex3_new)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(ex3_new main.cpp Command.h CommandTypes.cpp CommandTypes.h Interpreter.cpp Expression.h Interpreter.h)