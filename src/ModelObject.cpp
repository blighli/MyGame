//
// Created by liqilei on 2019-12-04.
//

#include "ModelObject.h"
#include <iostream>

ModelObject::ModelObject(){
    vertexNumber = 0;
    vertices = NULL;
}

GLuint ModelObject::getVertexNumber() const {
    return vertexNumber;
}

GLfloat *ModelObject::getVertices() const {
    return vertices;
}

void ModelObject::loadObject(const char *fileName) {
    FILE* file =  fopen(fileName, "r");
    if (!file)
    {
        std::cerr<<"Load object source " << fileName << " failed!"<<std::endl;
        return;
    }

    fscanf(file, "%d", &vertexNumber);

    //std::cout << "Object vertex number: " << vertexNumber << std::endl;

    int dataNumber = vertexNumber * 6;
    vertices = new GLfloat[dataNumber];
    for(int i=0; i<dataNumber; i++){
        fscanf(file, "%f", &vertices[i]);

        //std::cout << "Data " << vertices[i] << std::endl;
    }

    fclose(file);
}