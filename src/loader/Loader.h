#ifndef LOADER_H
#define LOADER_H

#pragma once

#include "model/RawModel.h"
#include <vector>
#include <iostream>

class Loader
{
public:
    Loader();
    ~Loader();

    RawModel *load(std::vector<float> &postions, std::vector<float> &colours, std::vector<int> &indices);
    RawModel *load(GLfloat *postions, int posLen, GLfloat *colours, int colourLen, GLint *indices, int idxLen);
};

#endif