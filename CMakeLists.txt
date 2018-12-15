cmake_minimum_required(VERSION 3.5)
project(Kopytko)

set(CMAKE_CXX_STANDARD 11)

# Enable proper linear algebra cpu instructions
if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
    add_definitions(-DUSE_AVX_INSTRUCTIONS=ON)
    set(CMAKE_CXX_FLAGS "-mavx")
else()
    add_definitions(-DUSE_NEON_INSTRUCTIONS=ON)
    set(CMAKE_CXX_FLAGS "-mfpu=neon")
endif()


# Set dlib build properties
add_definitions(-DLIB_LINK_WITH_FFTW=OFF)
add_definitions(-DDLIB_JPEG_SUPPORT)
add_definitions(-DLIB_LINK_WITH_LIBJPEG=ON)
add_definitions(-DLIB_LINK_WITH_LIBPNG=OFF)
add_definitions(-DLIB_LINK_WITH_SQLITE3=OFF)

# Add dlib subdirectory
add_subdirectory(./dlib dlib_build)


# Find reqired libs
find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED)
find_package(CURL REQUIRED)
find_package(ALSA REQUIRED)
find_package(SDL2 REQUIRED)
find_package(dkulpaclibs REQUIRED)
find_library(bluetooth_lib bluetooth REQUIRED)
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-2.4)

# Include libs directories
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

# Lins libs directories
link_directories(${GTKMM_LIBRARY_DIRS})


add_executable(Kopytko main.cpp UI/Views/ClockView.cpp UI/Views/ClockView.h UI/Views/Header.cpp UI/Views/Header.h Logic/AI/FaceRecognition/FaceRecognizer.cpp Logic/AI/FaceRecognition/FaceRecognizer.h UI/Views/DebugView.cpp UI/Views/DebugView.h Logic/AI/FaceRecognition/FaceModel.cpp Logic/AI/FaceRecognition/FaceModel.h UI/UI.cpp UI/UI.h UI/Views/HeartbeatView.cpp UI/Views/HeartbeatView.h UI/Views/ICMWeatherView.cpp UI/Views/ICMWeatherView.h Logic/AI/SpeechRecognition/SpeechListener.cpp Logic/AI/SpeechRecognition/SpeechListener.h DataProcessing/DataProcessor.cpp DataProcessing/DataProcessor.h Logic/AI/FaceRecognition/FaceNetTemplate.h Session.cpp Session.h Logic/AI/FaceRecognition/FaceFinder.cpp Logic/AI/FaceRecognition/FaceFinder.h UI/Voice.cpp UI/Voice.h Logic/AI/SpeechRecognition/SpectrumGatherer.cpp Logic/AI/SpeechRecognition/SpectrumGatherer.h UI/User.cpp UI/User.h Logic/AI/SpeechRecognition/TriggerWordDetector.cpp Logic/AI/SpeechRecognition/TriggerWordDetector.h Logic/Peripherals/PhoneConnectionManager.cpp Logic/Peripherals/PhoneConnectionManager.h Logic/Peripherals/HomeConnectionManager.cpp Logic/Peripherals/HomeConnectionManager.h)
target_link_libraries(Kopytko ${CMAKE_THREAD_LIBS_INIT} ${GTKMM_LIBRARIES} dlib::dlib ${OpenCV_LIBS} ${CURL_LIBRARIES} ${bluetooth_lib} ${SDL2_LIBRARIES} ${ALSA_LIBRARIES} SDL2_mixer fftw3f ${dkulpaclibs_misc_LIB} ${dkulpaclibs_hw_LIB} ${bluetooth_lib})