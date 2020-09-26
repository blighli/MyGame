set(SOURCE_FILES main.cpp render.cpp render.h ShaderProgram.cpp ShaderProgram.h WindowManager.cpp WindowManager.h ModelObject.cpp ModelObject.h)

if(APPLE)
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCE_FILES})
elseif(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})
endif()

target_link_libraries(${PROJECT_NAME} ${LIBS})

if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "${EXE_NAME}")
elseif(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()