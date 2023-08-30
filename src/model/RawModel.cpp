#include "RawModel.h"

RawModel::RawModel(GLuint vao, GLsizei vertexCount)
{
    this->vao = vao;
    this->vertexCount = vertexCount;
}

RawModel::~RawModel()
{
}