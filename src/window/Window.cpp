#include "Window.h"
#include <iostream>

Window::Window(std::string title, int width, int height) : title(title), width(width), height(height), currentScene(0)
{
    // 创建glfw窗体
    this->glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (this->glfwWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
}

Window::~Window()
{
}

void Window::render()
{

    if (this->currentScene)
    {
        this->currentScene->render();
    }
}

void Window::addScene(std::string sceneTitle, Scene *scene)
{
    if (this->scenes.size() == 0)
    {

        this->currentScene = scene;
        if (!this->currentScene)
        {
            this->currentScene->window = nullptr;
        }
        this->currentScene->window = this;
    }
    this->scenes[sceneTitle] = scene;
}

void Window::onMouseEvent(MouseEvent *mouseEvent)
{
    if (this->currentScene)
    {
        this->currentScene->onMouseEvent(mouseEvent);
    }
}
