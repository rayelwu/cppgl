#ifndef SHADER_H
#define SHADER_H

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_float4x4.hpp>

class Shader
{
public:
    GLuint Program;

    Shader(const GLchar *vertexShaderPath, const GLchar *fragmentShaderPath);
    ~Shader();

    void Use();
    void setUniform1f(const GLchar *name, GLfloat v0);
    void setUniformMatrix4fv(const GLchar *name, glm::mat4 trans);
    void setUniform3f(const GLchar *name, glm::vec3 vec);

private:
};

#endif