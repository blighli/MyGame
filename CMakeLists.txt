cmake_minimum_required(VERSION 3.9)

project(MyGame)

include_directories(include)

find_package(OpenGL)
list(APPEND LIBS "${OPENGL_LIBRARIES}")

if (APPLE)
    find_library(GLFW NAMES libglfw3.a PATHS lib/apple)
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
    find_library(LIBS NAMES glfw3.lib PATHS lib/msvc)
endif()
if (MINGW)
    find_library(LIBS NAMES libglfw3.a PATHS lib/mingw)
endif()

add_subdirectory(src)