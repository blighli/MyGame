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
    int *getElements() const;
    float *getVertices() const;
    float *getColors() const;
    void loadObject(const char* fileName);
    void createSphere();
    void createMat();
public:
    ModelObject();

private:
    int vertexCount;
    float* vertices;
    float* colors;
    int* elements;
    std::string name;
    int objectId;
    int drawMode;
public:
    int getDrawMode() const;
};


#endif //MYGAME_MODELOBJECT_H
