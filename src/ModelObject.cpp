//
// Created by liqilei on 2019-12-04.
//

#include "ModelObject.h"
#include <iostream>
#include "glm/gtc/type_ptr.hpp"

ModelObject::ModelObject(){
    objectId = 0;
    drawMode = 0;
    vertexCount = 0;
    vertices = NULL;
    colors = NULL;
    elements = NULL;
}
int ModelObject::getObjectId() const {
    return objectId;
}

void ModelObject::setObjectId(int objectId) {
    ModelObject::objectId = objectId;
}

int ModelObject::getDrawMode() const {
    return drawMode;
}

int ModelObject::getVertexCount() const {
    return vertexCount;
}

float *ModelObject::getVertices() const {
    return vertices;
}

float *ModelObject::getColors() const {
    return colors;
}

int *ModelObject::getElements() const {
    return elements;
}

void ModelObject::loadObject(const char *fileName) {
    FILE* file =  fopen(fileName, "r");
    if (!file)
    {
        std::cerr<<"Load model object " << fileName << " failed!"<<std::endl;
        return;
    }

    fscanf(file, "%d", &vertexCount);

    int vertexSize = vertexCount * 3;
    vertices = new float[vertexSize];
    for(int i=0; i < vertexSize; i++){
        fscanf(file, "%f", &vertices[i]);
    }

    int colorSize = vertexCount * 3;
    colors = new float[colorSize];
    for(int i=0; i < colorSize; i++){
        fscanf(file, "%f", &colors[i]);
    }

    fclose(file);
}

void ModelObject::createSphere() {
    int lats = 40;
    int longs = 40;

    vertexCount = lats * longs;

    int dataNumber = vertexCount * 6;
    vertices = new float[dataNumber];

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

void ModelObject::createMat() {
    int rows = 10;
    int cols = 10;
    vertexCount = rows * cols;
    vertices = new float[vertexCount * 3];
    colors = new float[vertexCount * 3];
    for(int i=0; i< rows; i++){
        for(int j=0; j<cols; j++){
            vertices[(i * cols + j) * 3 + 0] = 2.0 / cols * j - 1.0;
            vertices[(i * cols + j) * 3 + 1] = 2.0 / rows * i - 1.0;
            vertices[(i * cols + j) * 3 + 2] = 0.1;

            colors[(i * cols + j) * 3 + 0] = 1.0;
            colors[(i * cols + j) * 3 + 1] = 1.0;
            colors[(i * cols + j) * 3 + 2] = 1.0;
        }
    }

}





