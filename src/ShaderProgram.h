//
// Created by liqilei on 2019-11-28.
//

#ifndef MYGAME_SHADERPROGRAM_H
#define MYGAME_SHADERPROGRAM_H

#include <GL/glew.h>

class ShaderProgram {
public:
    ShaderProgram();
    virtual ~ShaderProgram();
    void loadShader(GLenum shaderType, const char* fileName);
    void use();
private:
    GLuint program;
    const char* loadSource(const char* fileName);
};


#endif //MYGAME_SHADERPROGRAM_H
