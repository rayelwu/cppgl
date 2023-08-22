#ifndef LOADER_H
#define LOADER_H

#pragma once

#include "model/RawModel.h"
#include <vector>

class Loader
{
public:
    Loader();
    ~Loader();

    RawModel *load(GLfloat *, int);
    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;

private:
};

#endif