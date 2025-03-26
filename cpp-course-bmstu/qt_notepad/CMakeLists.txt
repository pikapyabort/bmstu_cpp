cmake_minimum_required(VERSION 3.22)
project(qt_notepad)

set(CMAKE_PREFIX_PATH "Users/fenbcn/Qt/6.4.2/macos/lib/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
add_executable(qt_notepad editor.cpp editor.h highlighter.cpp highlighter.h main.cpp mainwindow.h mainwindow.cpp menu.cpp menu.h linenumberarea.cpp linenumberarea.h resources.qrc)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Qml
        Xml
        REQUIRED)

target_link_libraries(qt_notepad Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt6::Qml
        Qt::Xml)