set(SOURCE_FILES main.cpp render.cpp render.h ShaderProgram.cpp ShaderProgram.h WindowManager.cpp WindowManager.h ModelObject.cpp ModelObject.h)

#add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${LIBS})

#if(APPLE)
#    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "${EXE_NAME}")
#endif()
#if (MSVC)
#    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
#endif()