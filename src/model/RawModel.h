#ifndef RAWMODEL_H
#define RAWMODEL_H

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class RawModel
{
public:

    GLuint vao;
    GLsizei vertexCount;
    RawModel(GLuint, GLsizei);
    ~RawModel();

private:

};

#endif