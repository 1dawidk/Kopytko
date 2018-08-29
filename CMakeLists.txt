cmake_minimum_required(VERSION 3.12)
project(Kopytko)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(Kopytko main.cpp UI/AppMain.cpp UI/AppMain.h UI/Boxes/DebugBox.cpp UI/Boxes/DebugBox.h)
target_link_libraries(Kopytko ${GTKMM_LIBRARIES})