cmake_minimum_required(VERSION 3.12)
project(Kopytko)

set(CMAKE_CXX_STANDARD 11)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
    add_definitions(-DDEBUG1)
else()
    find_package(raspicam REQUIRED)
    find_library(bcm2835_lib bcm2835 REQUIRED)
    MESSAGE( STATUS "bcm2835 Library: " ${bcm2835_lib} )
    find_library(bluetooth_lib bluetooth REQUIRED)
    MESSAGE( STATUS "bluetooth Library: " ${bluetooth_lib} )
endif()

find_package( Threads REQUIRED)
find_package(dlib REQUIRED)
find_package(PkgConfig)
find_package( OpenCV REQUIRED )
pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(Kopytko main.cpp UI/AppMain.cpp UI/AppMain.h UI/Boxes/DebugBox.cpp UI/Boxes/DebugBox.h UI/Views/ClockView.cpp UI/Views/ClockView.h UI/Views/Header.cpp UI/Views/Header.h Misc/bcm2835.h Misc/Clock.cpp Misc/Clock.h Misc/Thread.cpp Misc/Thread.h HWDrivers/Camera.cpp HWDrivers/Camera.h AI/FaceRecognizer.cpp AI/FaceRecognizer.h)
target_link_libraries(Kopytko ${CMAKE_THREAD_LIBS_INIT} ${GTKMM_LIBRARIES} dlib::dlib ${OpenCV_LIBS})

if(NOT CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
    target_link_libraries(Kopytko ${bcm2835_lib} ${bluetooth_lib} ${raspicam_LIBS})
endif()