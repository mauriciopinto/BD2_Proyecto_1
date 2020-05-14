cmake_minimum_required(VERSION 3.12)
project(BD2_PROYECTO_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(BD2_PROYECTO_1 parser.cpp parser.h main.cpp statichashing.cpp statichashing.h randomfile.cpp randomfile.h record.cpp record.h transactions.cpp transactions.h ui/input.cpp ui/input.h ui/ui_dialog.h ui/mainwindow.h ui/mainwindow.cpp)