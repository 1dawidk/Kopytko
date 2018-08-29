cmake_minimum_required(VERSION 3.7)
project(misc)

set(CMAKE_CXX_STANDARD 11)

find_package( Threads REQUIRED)

set(SOURCE_FILES ConfigManager.cpp ConfigManager.h Thread.cpp Thread.h TalkManager.cpp TalkManager.h ExtString.cpp ExtString.h Clock.cpp Clock.h GlobalLog.cpp GlobalLog.h)
add_library(misc SHARED ${SOURCE_FILES})
target_link_libraries(misc ${CMAKE_THREAD_LIBS_INIT})