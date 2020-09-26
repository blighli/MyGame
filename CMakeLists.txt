cmake_minimum_required(VERSION 3.16)

project(MyGame)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_SOURCE_DIR}/bin")

include_directories(include)

find_package(OpenGL)

if (APPLE)
    find_library(GLFW NAMES libglfw3.a PATHS lib/apple)
    find_library(GLEW NAMES libGLEW.a PATHS lib/apple)
    find_library(FreeImage NAMES libfreeimage.a PATHS lib/apple)
    find_library(COCOA_FRAMEWORK Cocoa)
    find_library(IOKIT_FRAMEWORK IOKit)
    find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
    find_library(CORE_VIDEO_FRAMEWORK CoreVideo)
    list(APPEND LIBS
            "${COCOA_FRAMEWORK}"
            "${IOKIT_FRAMEWORK}"
            "${CORE_FOUNDATION_FRAMEWORK}"
            "${CORE_VIDEO_FRAMEWORK}")
elseif(WIN32)
    find_library(GLFW NAMES glfw3dll.lib PATHS lib/win32)
    find_library(GLEW NAMES glew32s.lib PATHS lib/win32)
    find_library(FreeImage NAMES FreeImage.lib PATHS lib/win32)
endif()

list(APPEND LIBS
        "${GLFW}"
        "${GLEW}"
        "${FreeImage}"
        "${OPENGL_LIBRARIES}")

add_definitions(-DGLEW_STATIC)

add_subdirectory(src)
