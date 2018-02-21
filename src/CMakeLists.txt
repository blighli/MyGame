cmake_minimum_required(VERSION 3.9)

include_directories(../include)

if (APPLE)
    find_library(LIBS NAMES libglfw3.a PATHS ../lib/macosx)
endif()
if (MSVC)
    find_library(LIBS NAMES glfw3.lib PATHS ../lib/win32)
endif()
if (MINGW)
    find_library(LIBS NAMES libglfw3.a PATHS ../lib/mingw)
endif()

set(SOURCE_FILES main.cpp)

add_executable(MyGame ${SOURCE_FILES})

message(STATUS "Library path is " ${LIBS})

target_link_libraries(MyGame ${LIBS})