#include "App.h"
#include <iostream>

App::App()
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
}

App::~App()
{
}

Window *App::createWindow(std::string title, int width, int height)
{
    Window *window = new Window(title, width, height);
    setWindow(window);
    return window;
}

const void App::setWindow(Window *currentWindow)
{
    this->currentWindow = currentWindow;
    glfwMakeContextCurrent(this->currentWindow->glfwWindow);
    glfwSetFramebufferSizeCallback(this->currentWindow->glfwWindow, App::onGlfwResize);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

/**
 *
 * Application main loop
 */
const void App::loop()
{
    GLFWwindow *glfwWindow = this->currentWindow->glfwWindow;
    while (!glfwWindowShouldClose(glfwWindow))
    {
        this->onGlfwInput(glfwWindow);
        this->currentWindow->render();
        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }
}

/**
 * Cancel memory allocation
 *
 */
int App::exit() const
{
    glfwTerminate();
    return 0;
}

// 每当窗口大小发生变化（通过OS或用户调整大小）时，都会执行此回调函数
void App::onGlfwResize(GLFWwindow *window, int width, int height)
{
    // 确保视口与新窗口尺寸匹配; 请注意宽度和
    // 高度将远远大于视网膜显示器上指定的高度。
    glViewport(0, 0, width, height);
}

// glfw：点击esc退出，可是删掉这一块前面的东西还会报错，还是留着吧
void App::onGlfwInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    double worldX = (mouseX / this->currentWindow->width) * 2.0f - 1.0f;
    double worldY = (1 - mouseY / this->currentWindow->height) * 2.0f - 1.0f;
    std::cout << "(" << worldX << "," << worldY << ")" << std::endl;
    this->currentWindow->onMouseEvent(new MouseEvent{mouseX, mouseY, worldX, worldY});
}
