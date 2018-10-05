cmake_minimum_required(VERSION 3.5)
project(Kopytko)

set(CMAKE_CXX_STANDARD 11)


if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
    add_definitions(-DUSE_AVX_INSTRUCTIONS=ON)
    set(CMAKE_CXX_FLAGS "-mavx")
else()
    add_definitions(-DUSE_NEON_INSTRUCTIONS=ON)
    set(CMAKE_CXX_FLAGS "-mfpu=neon")
    find_package(raspicam REQUIRED)
    find_library(bluetooth_lib bluetooth REQUIRED)
    MESSAGE( STATUS "bluetooth Library: " ${bluetooth_lib} )
endif()

if(${BOARD_TYPE} MATCHES RASPBERRY_PI)
    message("BOARD TYPE: It is Raspberry Pi")
    add_definitions(-DBOARD_TYPE_RASPBERRYPI)
else()
    message("BOARD TYPE: It is standard board")
    add_definitions(-DBOARD_TYPE_STD)
endif()

add_definitions(-DLIB_LINK_WITH_FFTW=OFF)
add_definitions(-DDLIB_JPEG_SUPPORT)
add_definitions(-DLIB_LINK_WITH_LIBJPEG=ON)
add_definitions(-DLIB_LINK_WITH_LIBPNG=OFF)
add_definitions(-DLIB_LINK_WITH_SQLITE3=OFF)

add_subdirectory(./dlib dlib_build)

find_package(Threads REQUIRED)
find_package(PkgConfig)
find_package(OpenCV REQUIRED)
find_package(CURL REQUIRED)
pkg_check_modules(GTKMM gtkmm-2.4)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(Kopytko main.cpp UI/Views/ClockView.cpp UI/Views/ClockView.h UI/Views/Header.cpp UI/Views/Header.h Misc/bcm2835.h Misc/Clock.cpp Misc/Clock.h Misc/Thread.cpp Misc/Thread.h HWDrivers/Camera.cpp HWDrivers/Camera.h AI/FaceRecognizer.cpp AI/FaceRecognizer.h UI/Context.cpp UI/Context.h UI/Views/DebugView.cpp UI/Views/DebugView.h UI/Views/CPUTempView.cpp UI/Views/CPUTempView.h AI/FaceModel.cpp AI/FaceModel.h UI/MainContext.cpp UI/MainContext.h UI/Views/HeartbeatView.cpp UI/Views/HeartbeatView.h UI/Views/ICMWeatherView.cpp UI/Views/ICMWeatherView.h UI/Views/BatteryView.cpp UI/Views/BatteryView.h UI/AsyncTask.cpp UI/AsyncTask.h)
target_link_libraries(Kopytko ${CMAKE_THREAD_LIBS_INIT} ${GTKMM_LIBRARIES} dlib::dlib ${OpenCV_LIBS} ${CURL_LIBRARIES})

if(RUN_DEFS MATCHES "BOARD_TYPE_RASPBERRYPI")
    target_link_libraries(Kopytko ${bluetooth_lib} ${raspicam_CV_LIBS})
endif()