set(EXE_NAME MyGame)
set(SOURCE_FILES main.cpp)

add_executable(${EXE_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

target_link_libraries(${EXE_NAME} ${LIBS})

if(APPLE)
    set_target_properties(${EXE_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "${EXE_NAME}")
endif()
if (MSVC)
    set_target_properties(${EXE_NAME} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()