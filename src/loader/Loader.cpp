#include "Loader.h"
#include <iostream>
Loader::Loader()
{
}

Loader::~Loader()
{
}

template <typename T>
T *vec2arr(std::vector<T> vec)
{
    T *arr = (T *)malloc(sizeof(T) * vec.size());
    std::copy(vec.begin(), vec.end(), arr);
    return arr;
}

template <typename T>
void debug(T *postions, int posLen)
{
    std::cout << "Length: " << posLen << std::endl;
    for (size_t i = 0; i < posLen; i++)
    {
        std::cout << postions[i] << ", ";
    }
    std::cout << std::endl;
}

RawModel *Loader::load(std::vector<float> &postions, std::vector<float> &colours, std::vector<int> &indices)
{
    return this->load(
        vec2arr(postions), postions.size(),
        vec2arr(colours), colours.size(),
        vec2arr(indices), indices.size());
}

RawModel *Loader::load(GLfloat *postions, int posLen, GLfloat *colors, int colourLen, GLint *indices, int idxLen)
{
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    debug(postions, posLen);
    debug(colors, colourLen);
    debug(indices, idxLen);

    // load postions
    GLuint position;
    
    glGenBuffers(1, &position);
    glBindBuffer(GL_ARRAY_BUFFER, position);
    glBufferData(GL_ARRAY_BUFFER, posLen * sizeof(GLfloat), postions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (GLvoid *)0);
    glEnableVertexAttribArray(0);
    

    // load colors
    GLuint color;
    glGenBuffers(1, &color);
    glBindBuffer(GL_ARRAY_BUFFER, color);
    glBufferData(GL_ARRAY_BUFFER, colourLen * sizeof(GLfloat), colors, GL_STATIC_DRAW);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, (GLvoid *)0);
    glEnableVertexAttribArray(1);

    // load indices
    GLuint idx;
    glGenBuffers(1, &idx);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, idxLen * sizeof(GLint), indices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return new RawModel(vao, idxLen);
}