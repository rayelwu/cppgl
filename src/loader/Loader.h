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

    RawModel *load(GLfloat *postions, GLfloat *colours, GLint *indices);
    RawModel *loadCube(GLfloat *postions, GLfloat *colours, GLint *indices);
    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;

private:
    GLuint createVertexBuffer(GLenum target, const void* vertexArray, int vertexCount, int vertexStride);
};

#endif