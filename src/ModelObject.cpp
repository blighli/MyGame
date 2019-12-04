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
    indices = NULL;
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

int *ModelObject::getIndices() const {
    return indices;
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
    float width = 2.0f;
    float height = 2.0f;

    vertexCount = (rows) * (cols) * 6;
    vertices = new float[vertexCount * 3];
    colors = new float[vertexCount * 3];
    int vertexIndex = 0;
    int colorIndex = 0;
    float xMin = -width/2;
    float yMin = -height/2;
    float xStep = width/cols;
    float yStep = height/rows;
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){

            float xBase = xMin + xStep*j;
            float yBase = yMin + yStep*i;

            vertices[vertexIndex++] = xBase;
            vertices[vertexIndex++] = yBase;
            vertices[vertexIndex++] = 0.1;

            vertices[vertexIndex++] = xBase + xStep;
            vertices[vertexIndex++] = yBase;
            vertices[vertexIndex++] = 0.1;

            vertices[vertexIndex++] = xBase;
            vertices[vertexIndex++] = yBase + yStep;
            vertices[vertexIndex++] = 0.1;

            vertices[vertexIndex++] = xBase + xStep;
            vertices[vertexIndex++] = yBase;
            vertices[vertexIndex++] = 0.1;

            vertices[vertexIndex++] = xBase;
            vertices[vertexIndex++] = yBase + yStep;
            vertices[vertexIndex++] = 0.1;

            vertices[vertexIndex++] = xBase + xStep;
            vertices[vertexIndex++] = yBase + yStep;
            vertices[vertexIndex++] = 0.1;

            float colorValue = 1.0;
            if(i%2 == 0 && j%2 != 0 || i%2 != 0 && j%2 == 0)
            {
                colorValue = 0.0;
            }
            for(int k=0; k<6; k++)
            {
                colors[colorIndex++] = colorValue;
                colors[colorIndex++] = colorValue;
                colors[colorIndex++] = colorValue;
            }

        }
    }

}

int ModelObject::getIndexCount() const {
    return indexCount;
}





