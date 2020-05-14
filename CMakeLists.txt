cmake_minimum_required(VERSION 3.12)
project(BD2_PROYECTO_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/Users/jonathanprieto/Qt5.13.0/5.13.0/clang_64/lib/cmake")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(BD2_PROYECTO_1 parser.cpp parser.h main.cpp statichashing.cpp statichashing.h randomfile.cpp randomfile.h record.cpp record.h transactions.cpp transactions.h ui/input.cpp ui/input.h ui/ui_dialog.h ui/mainwindow.h ui/mainwindow.cpp ui/mainwindow.ui ui/ui_input.ui ui/input.h ui/dialog.ui ui/input.ui ui/ui_input.h ui/ui_mainwindow.h)
target_link_libraries(BD2_PROYECTO_1 Qt5::Widgets)