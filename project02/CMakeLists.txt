project(project02)

set(SOURCE_FILES main.cpp Shader.cpp Shader.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${LIBS})