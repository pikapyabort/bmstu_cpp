cmake_minimum_required(VERSION 3.22)
project(qt_xml)

set(CMAKE_PREFIX_PATH "Users/fenbcn/Qt/6.4.2/macos/lib/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
add_executable(qt_xml  mainwindow.cpp mainwindow.h xmlmodel.cpp xmlmodel.h main.cpp)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Qml
        REQUIRED)

target_link_libraries(qt_xml Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt6::Qml)