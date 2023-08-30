#ifndef SHADER_H
#define SHADER_H

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
    GLuint Program;
    
    Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
    ~Shader();
    
    void Use();
    void setUniform1f(const GLchar *name, GLfloat v0);
private:
};

#endif