cmake_minimum_required(VERSION 3.12)
project(Kopytko)

set(CMAKE_CXX_STANDARD 11)

find_package( Threads REQUIRED)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(Kopytko main.cpp UI/AppMain.cpp UI/AppMain.h UI/Boxes/DebugBox.cpp UI/Boxes/DebugBox.h UI/Views/ClockView.cpp UI/Views/ClockView.h UI/Views/Header.cpp UI/Views/Header.h Misc/bcm2835.h Misc/Clock.cpp Misc/Clock.h Misc/Thread.cpp Misc/Thread.h)
target_link_libraries(Kopytko ${CMAKE_THREAD_LIBS_INIT} ${GTKMM_LIBRARIES})