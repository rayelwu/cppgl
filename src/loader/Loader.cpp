#include "Loader.h"

Loader::Loader()
{

}

Loader::~Loader()
{
    for (size_t i = 0; i < vaos.size(); i++)
    {
        glDeleteVertexArrays(1,&vaos[i]);
    }
    for (size_t i = 0; i < vbos.size(); i++)
    {
        glDeleteBuffers(1,&vbos[i]);
    }
}

RawModel *Loader::load(GLfloat *positions, int vertexSize)
{
    
    RawModel* model = new RawModel();
    glGenVertexArrays(1, &model->vao);

    this->vaos.push_back(model->vao);

    glBindVertexArray(model->vao);
    GLuint vbo;
    glGenBuffers(1, &vbo);

    this->vbos.push_back(vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);


    return model;
}
