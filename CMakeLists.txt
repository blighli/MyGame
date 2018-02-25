cmake_minimum_required(VERSION 3.9)

set (CMAKE_CXX_STANDARD 11)

include_directories(include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_SOURCE_DIR}/bin")

if (APPLE)
    find_library(GLFW NAMES libglfw3.a PATHS lib/apple)
    find_library(GLEW NAMES libGLEW.a PATHS lib/apple)
    find_library(COCOA_FRAMEWORK Cocoa)
    find_library(IOKIT_FRAMEWORK IOKit)
    find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
    find_library(CORE_VIDEO_FRAMEWORK CoreVideo)
    list(APPEND LIBS
            "${COCOA_FRAMEWORK}"
            "${IOKIT_FRAMEWORK}"
            "${CORE_FOUNDATION_FRAMEWORK}"
            "${CORE_VIDEO_FRAMEWORK}")
endif()
if (MSVC)
    find_library(GLFW NAMES glfw3.lib PATHS lib/msvc)
    find_library(GLEW NAMES glew32s.lib PATHS lib/msvc)
endif()
if (MINGW)
    find_library(GLFW NAMES libglfw3.a PATHS lib/mingw)
    find_library(GLEW NAMES libglew32.a PATHS lib/mingw)
endif()

add_definitions(-DGLEW_STATIC)

find_package(OpenGL)

list(APPEND LIBS
        "${GLFW}"
        "${GLEW}"
        "${OPENGL_LIBRARIES}")

add_subdirectory(src)
add_subdirectory(project01)
add_subdirectory(project02)