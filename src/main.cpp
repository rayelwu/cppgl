#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <cmath>
#include <shader/Shader.h>

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

    Shader defaultShader("../res/vertex.glsl", "../res/fragment.glsl");

    // 设置顶点
    float vertices[] = {
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   // top
    };
    // 创建一个VAO——顶点数组对象(Vertex Array Object, VAO)
    //         VAO可以像顶点缓冲对象那样被绑定，任何随后的顶点属性调用都会储存在这个VAO中。
    // 创建VBO——顶点缓冲对象：Vertex Buffer Object，VBO
    //         它会在GPU内存（通常被称为显存）中储存大量顶点。
    //         使用这些缓冲对象的好处是我们可以一次性的发送一大批数据到显卡上，而不是每个顶点发送一次。
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // 1.绑定VOA
    glBindVertexArray(VAO);
    // 2.把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /*
    GL_STATIC_DRAW ：数据不会或几乎不会改变。
    GL_DYNAMIC_DRAW：数据会被改变很多。
    GL_STREAM_DRAW ：数据每次绘制时都会改变。
    */

    // 3.设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *)(3 * sizeof(GLfloat)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAO);

    // 循环渲染
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // 输入
        processInput(window);

        // 渲染
        // 清楚颜色缓冲
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 记得激活着色器
        defaultShader.Use();

        // 更新uniform，然后每个渲染迭代都更新这个uniform：
        /*
        首先我们通过glfwGetTime()获取运行的秒数。
        然后我们使用sin函数让颜色在0.0到1.0之间改变，
        最后将结果储存到greenValue里。
        */
        float timeValue = glfwGetTime();
        float alphaValue = sin(timeValue) / 2.0f + 0.5f;
        /*
        用glGetUniformLocation查询uniform ourColor的位置值。
        如果glGetUniformLocation返回-1就代表没有找到这个位置值。

        注意，查询uniform地址不要求你之前使用过着色器程序，
        但是更新一个uniform之前你必须先使用程序（调用glUseProgram)，
        因为它是在当前激活的着色器程序中设置uniform的。
        */
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "aColor");
        //  最后，我们可以通过glUniform4f函数设置uniform值。
        glUniform1f(glGetUniformLocation(defaultShader.Program, "aAplha"), alphaValue);

        // 绘制三角形
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 交换缓冲并查询IO事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 取消分配的空间
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

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