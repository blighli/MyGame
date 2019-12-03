//
// Created by liqilei on 2019-12-04.
//

#ifndef MYGAME_MODELOBJECT_H
#define MYGAME_MODELOBJECT_H


#include <GL/gl.h>

class ModelObject {
    GLuint vertexNumber;
    GLfloat* vertices;
public:
    GLuint getVertexNumber() const;
    GLfloat *getVertices() const;
    void loadObject(const char* fileName);
    void createSphere();
public:
    ModelObject();
};


#endif //MYGAME_MODELOBJECT_H
