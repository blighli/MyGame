//
// Created by liqilei on 2019-12-04.
//

#ifndef MYGAME_MODELOBJECT_H
#define MYGAME_MODELOBJECT_H

#include <string>

class ModelObject {

public:
    void setObjectId(int objectId);
    int getObjectId() const;
    int getVertexCount() const;
    int *getIndices() const;
    float *getVertices() const;
    float *getColors() const;
    void loadObject(const char* fileName);
    void createSphere();
    void createMat();
public:
    ModelObject();

private:
    int vertexCount;
    int indexCount;
public:
    int getIndexCount() const;

private:
    float* vertices;
    float* colors;
    int* indices;
    std::string name;
    int objectId;
    int drawMode;
public:
    int getDrawMode() const;
};


#endif //MYGAME_MODELOBJECT_H
