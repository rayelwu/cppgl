#include "App.h"
#include <iostream>
#include <functional>
App::App()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

App::~App()
{
}

Window *App::createWindow(std::string title, int width, int height)
{
    App::winWidth = width;
    App::winHeight = width;
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
        float currentFrame = static_cast<float>(glfwGetTime());
        this->deltaTime = currentFrame - this->lastFrame;
        this->lastFrame = currentFrame;

        this->currentWindow->width = App::winWidth;
        this->currentWindow->height = App::winHeight;
        this->onGlfwInput(glfwWindow);

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

void App::onGlfwResize(GLFWwindow *window, int width, int height)
{
    App::winWidth = width;
    App::winHeight = width;
    glViewport(0, 0, width, height);
}

void App::onGlfwInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        this->currentWindow->currentScene->camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        this->currentWindow->currentScene->camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        this->currentWindow->currentScene->camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        this->currentWindow->currentScene->camera->ProcessKeyboard(RIGHT, deltaTime);

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    double worldX = (mouseX / this->currentWindow->width) * 2.0f - 1.0f;
    double worldY = (1 - mouseY / this->currentWindow->height) * 2.0f - 1.0f;
    // std::cout << "(" << worldX << "," << worldY << ")" << std::endl;
    this->currentWindow->onMouseEvent(new MouseEvent{mouseX, mouseY, worldX, worldY});
}

int App::winWidth;
int App::winHeight;