#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>

int success;       // 表示是否编译成功
char infoLog[512]; // 存储错误信息

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

GLuint loadShader(GLuint program, GLuint type, const GLchar *const source, const GLint sourceLen)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    glAttachShader(program, shader);
    glDeleteShader(shader);
}

int loadShaderFromFile(GLuint program, GLuint type, const char *pathToGlsl)
{
    std::ifstream glslSourceFile;
    glslSourceFile.open(pathToGlsl, std::ios::in);
    if (!glslSourceFile)
    {
        std::cerr << "file: " << pathToGlsl << " open failed!" << std::endl;
        return -1;
    }
    std::string buffer, glslSource;
    while (std::getline(glslSourceFile, buffer))
    {
        glslSource.append(buffer).append("\n");
    }

    glslSourceFile.close();
    std::cout << glslSource.c_str() << std::endl;
    loadShader(program, type, glslSource.c_str(), glslSource.length());
    return 0;
}

void appRender()
{
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MAC OSX needs

    GLFWwindow *window = glfwCreateWindow(800, 600, "CppGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    GLuint program = glCreateProgram();
    loadShaderFromFile(program, GL_VERTEX_SHADER, "vertex.glsl");
    loadShaderFromFile(program, GL_FRAGMENT_SHADER, "fragment.glsl");
    glLinkProgram(program);
    // 错误检测
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
    float vertices[] = {
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        0.0f, 0.5f, 0.0f    // top
    };
    float colors[] = {
        1.0f, 0.0f, 0.0f, // 右下
        0.0f, 1.0f, 0.0f, // 左下
        0.0f, 0.0f, 1.0f  // 顶部
    };

    unsigned int vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(vao, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(vao);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        float timeValue = glfwGetTime();
        float greenValue = std::sin(timeValue) / 2.0f + 0.5f;

        int vertexColorLocation = glGetUniformLocation(program, "ourColor");
        // 最后，我们可以通过glUniform4f函数设置uniform值。
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        // 绘制三角形
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
        appRender();
    }
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glfwTerminate();

    return 0;
}
