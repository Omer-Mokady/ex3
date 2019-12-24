cmake_minimum_required(VERSION 3.15)
project(ex3_new)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(ex3_new main.cpp Command.h Interpreter.cpp Expression.h Interpreter.h OpenServerCommand.cpp OpenServerCommand.h ConnectCommand.cpp ConnectCommand.h DefineVarCommand.cpp DefineVarCommand.h Parser.h Parser.cpp Var.cpp Var.h Singleton.cpp Singleton.h)