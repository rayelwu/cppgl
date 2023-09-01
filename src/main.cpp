#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <cmath>
#include <shader/Shader.h>
#include <loader/Loader.h>
#include <renderer/Renderer.h>
#include <model/RawModel.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// 设置窗体的宽度和高度
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // 初始化glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 条件编译语句，如果是苹果系统？
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // 创建glfw窗体
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 设置顶点
    float postions[] = {
        0.5f, -0.5f, 0.0f, 
        -0.5f, -0.5f, 0.0f, 
        -0.5f, 0.5f, 0.0f, 
        0.5f, 0.5f, 0.0f, 
    };
    float colours[] = {
        1.0f, 0.0f, 0.0f, 
        0.0f, 1.0f, 0.0f, 
        0.0f, 0.0f, 1.0f, 
        1.0f, 0.0f, 0.0f, 
    };
    int indices[] = {0,1,2,3,0,2};

    
    Loader loader;
    Shader shader("../res/vertex.glsl", "../res/fragment.glsl");
    Renderer renderer(&shader);
    RawModel* model = loader.load(postions, colours, indices);
    

    // 循环渲染
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // 输入
        processInput(window);
        renderer.clear();
        shader.setUniform1f("aAplha", sin(glfwGetTime()) / 2.0f + 0.5f);
        renderer.render(model);
        // 交换缓冲并查询IO事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 取消分配的空间
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);

    // 终止，清除所有先前分配的GLFW资源。
    glfwTerminate();
    return 0;
}

// glfw：点击esc退出，可是删掉这一块前面的东西还会报错，还是留着吧
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// 每当窗口大小发生变化（通过OS或用户调整大小）时，都会执行此回调函数
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // 确保视口与新窗口尺寸匹配; 请注意宽度和
    // 高度将远远大于视网膜显示器上指定的高度。
    glViewport(0, 0, width, height);
}