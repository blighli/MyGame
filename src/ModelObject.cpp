//
// Created by liqilei on 2019-12-04.
//

#include "ModelObject.h"
#include <iostream>
#include "glm/gtc/type_ptr.hpp"

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

void ModelObject::createSphere() {
    int lats = 40;
    int longs = 40;

    vertexNumber = lats * longs;

    int dataNumber = vertexNumber * 6;
    vertices = new GLfloat[dataNumber];

    for(int i = 0; i <= lats; i++) {
        double lat0 = glm::pi<double>() * (-0.5 + (double) (i - 1) / lats);
        double z0 = sin(lat0);
        double zr0 = cos(lat0);

        double lat1 = glm::pi<double>() * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        for (int j = 0; j <= longs; j++) {
            double lng = 2 * glm::pi<double>() * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

            vertices[i*longs + j] = (x * zr0);
            vertices[i*longs + j + 1] = (y * zr0);
            vertices[i*longs + j + 2]= (z0);

            vertices[i*longs + j + 3] = (x * zr1);
            vertices[i*longs + j + 4] = (y * zr1);
            vertices[i*longs + j + 5] = (z1);
        }
    }
}
