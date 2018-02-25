//
// Created by liqilei on 2018/2/25.
//

#include "Shader.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

string ReadFile(string filename) {
    ifstream inFile;
    inFile.open(filename);

    stringstream strStream;
    strStream << inFile.rdbuf();

    inFile.close();

    return strStream.str();
}