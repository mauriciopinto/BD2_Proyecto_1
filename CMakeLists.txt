cmake_minimum_required(VERSION 3.12)
project(BD2_PROYECTO_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(BD2_PROYECTO_1 main.cpp parser.cpp parser.h randomfile.cpp randomfile.h statichashing.cpp statichashing.h transactions.cpp transactions.h ui.cpp ui.h)