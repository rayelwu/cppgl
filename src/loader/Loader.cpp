#include "Loader.h"
#include <iostream>
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
        glDeleteBuffers(1, &vbos[i]);
    }
}


GLuint Loader::createVertexBuffer(GLenum target, const void* vertexArray, int vertexCount, int vertexStride) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(target, vbo);
    glBufferData(target, vertexCount * vertexStride * sizeof(GLfloat), vertexArray, GL_STATIC_DRAW);
    GLint vboid = this->vbos.size();
    glVertexAttribPointer(vboid, vertexCount, GL_FLOAT, false, vertexStride * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(vboid);
    this->vbos.push_back(vbo);
    return vbo;
}



RawModel *Loader::load(GLfloat *postions, GLfloat *colours, GLint *indices)
{
    
    //RawModel* model = new RawModel();
    GLuint vao,vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // glGenBuffers(1, &vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, length * sizeof(GLfloat), vertexArray, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, vertexCount, GL_FLOAT, false, 6 * sizeof(GLfloat), (GLvoid*)0);
    // glEnableVertexAttribArray(0);
    this->createVertexBuffer(GL_ARRAY_BUFFER, postions, 4, 3);
    this->createVertexBuffer(GL_ARRAY_BUFFER, colours, 4, 3);
    this->createVertexBuffer(GL_ELEMENT_ARRAY_BUFFER, indices, 6, 1);

    // glVertexAttribPointer(1, vertexCount, GL_FLOAT, false, 6 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
    // glEnableVertexAttribArray(1);

    glBindVertexArray(vao);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *)(3 * sizeof(GLfloat)));

    this->vaos.push_back(vao);

    return new RawModel(vao, 6);
}




RawModel *Loader::loadCube(GLfloat *postions, GLfloat *colours, GLint *indices)
{
    
    //RawModel* model = new RawModel();
    GLuint vao,vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // glGenBuffers(1, &vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, length * sizeof(GLfloat), vertexArray, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, vertexCount, GL_FLOAT, false, 6 * sizeof(GLfloat), (GLvoid*)0);
    // glEnableVertexAttribArray(0);
    this->createVertexBuffer(GL_ARRAY_BUFFER, postions, 8, 3);
    this->createVertexBuffer(GL_ARRAY_BUFFER, colours, 8, 3);
    this->createVertexBuffer(GL_ELEMENT_ARRAY_BUFFER, indices, 36, 1);

    // glVertexAttribPointer(1, vertexCount, GL_FLOAT, false, 6 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
    // glEnableVertexAttribArray(1);

    glBindVertexArray(vao);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *)(3 * sizeof(GLfloat)));

    this->vaos.push_back(vao);

    return new RawModel(vao, 36);
}
