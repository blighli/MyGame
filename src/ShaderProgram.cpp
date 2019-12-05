//
// Created by liqilei on 2019-11-28.
//

#include "ShaderProgram.h"
#include <iostream>

const char *ShaderProgram::loadSource(const char *fileName) {
    FILE* file =  fopen(fileName, "rb");
    if (!file)
    {
        std::cerr<<"Load shader source " << fileName << " failed!"<<std::endl;
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    int len = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* source = new char[len+1];
    fread(source, 1, len, file);
    fclose(file);

    source[len] = 0;

    return const_cast<const char*>(source);
}

ShaderProgram::ShaderProgram() {
    program = glCreateProgram();
}

void ShaderProgram::loadShader(GLenum shaderType, const char *fileName) {
    GLuint shader = glCreateShader(shaderType);
    const char* source = loadSource(fileName);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr<<"Shader Compile Error: " << infoLog << std::endl;
    }
    glAttachShader(program, shader);
}

void ShaderProgram::use() {
    glLinkProgram(program);
    glUseProgram(program);
}

ShaderProgram::~ShaderProgram() {

}
