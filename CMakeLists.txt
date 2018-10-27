cmake_minimum_required(VERSION 3.5)
project(Kopytko)

set(CMAKE_CXX_STANDARD 11)


if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
    add_definitions(-DUSE_AVX_INSTRUCTIONS=ON)
    set(CMAKE_CXX_FLAGS "-mavx")
else()
    add_definitions(-DUSE_NEON_INSTRUCTIONS=ON)
    set(CMAKE_CXX_FLAGS "-mfpu=neon")
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
find_package(ALSA REQUIRED)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

SET(GCC_COVERAGE_LINK_FLAGS "-lSDL2_mixer -lm -lfftw3f")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

pkg_check_modules(GTKMM gtkmm-2.4)

find_library(bluetooth_lib bluetooth REQUIRED)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(Kopytko main.cpp UI/Views/ClockView.cpp UI/Views/ClockView.h UI/Views/Header.cpp UI/Views/Header.h Logic/Misc/Clock.cpp Logic/Misc/Clock.h Logic/Misc/Thread.cpp Logic/Misc/Thread.h Logic/HWDrivers/Camera.cpp Logic/HWDrivers/Camera.h Logic/AI/FaceRecognition/FaceRecognizer.cpp Logic/AI/FaceRecognition/FaceRecognizer.h UI/Views/DebugView.cpp UI/Views/DebugView.h Logic/AI/FaceRecognition/FaceModel.cpp Logic/AI/FaceRecognition/FaceModel.h UI/UI.cpp UI/UI.h UI/Views/HeartbeatView.cpp UI/Views/HeartbeatView.h UI/Views/ICMWeatherView.cpp UI/Views/ICMWeatherView.h Logic/AI/VoiceRecognition/VoiceRecognizer.cpp Logic/AI/VoiceRecognition/VoiceRecognizer.h Logic/HWDrivers/BluetoothManager.h Logic/HWDrivers/BluetoothManager.cpp Logic/HWDrivers/BtRFCOMMServer.h Logic/HWDrivers/BtRFCOMMServer.cpp DataProcessing/DataProcessor.cpp DataProcessing/DataProcessor.h Logic/AI/FaceRecognition/FaceNetTemplate.h Session.cpp Session.h Logic/AI/FaceRecognition/FaceFinder.cpp Logic/AI/FaceRecognition/FaceFinder.h UI/Voice.cpp UI/Voice.h Logic/HWDrivers/SoundRecorder.cpp Logic/HWDrivers/SoundRecorder.h Logic/AI/VoiceRecognition/SpectrumGatherer.cpp Logic/AI/VoiceRecognition/SpectrumGatherer.h)
target_link_libraries(Kopytko ${CMAKE_THREAD_LIBS_INIT} ${GTKMM_LIBRARIES} dlib::dlib ${OpenCV_LIBS} ${CURL_LIBRARIES} ${bluetooth_lib} ${SDL2_LIBRARIES} ${ALSA_LIBRARIES})

if(${BOARD_TYPE} MATCHES RASPBERRY_PI)
    target_link_libraries(Kopytko ${bluetooth_lib})
endif()