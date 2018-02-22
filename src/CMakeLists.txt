cmake_minimum_required(VERSION 3.9)

include_directories(../include)

find_package(OpenGL)
list(APPEND LIBS "${OPENGL_LIBRARIES}")

if (APPLE)
    find_library(GLFW NAMES libglfw3.a PATHS ../lib/macosx)
    find_library(COCOA_FRAMEWORK Cocoa)
    find_library(IOKIT_FRAMEWORK IOKit)
    find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
    find_library(CORE_VIDEO_FRAMEWORK CoreVideo)
    list(APPEND LIBS "${GLFW}"
            "${COCOA_FRAMEWORK}"
            "${IOKIT_FRAMEWORK}"
            "${CORE_FOUNDATION_FRAMEWORK}"
            "${CORE_VIDEO_FRAMEWORK}")
endif()
if (MSVC)
    find_library(LIBS NAMES glfw3.lib PATHS ../lib/win32)
endif()
if (MINGW)
    find_library(LIBS NAMES libglfw3.a PATHS ../lib/mingw)
endif()

set(SOURCE_FILES main.cpp)

add_executable(MyGame ${SOURCE_FILES})

target_link_libraries(MyGame ${LIBS})