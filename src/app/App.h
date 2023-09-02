#ifndef APP_H
#define APP_H

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <window/Window.h>

class App
{
public:
    App();

    ~App();

    Window *currentWindow;

    Window *createWindow(std::string title, int width, int height);

    const void setWindow(Window *currentWindow);

    const void loop();

    int exit() const;

public:
    static void onGlfwResize(GLFWwindow *window, int width, int height);

     void onGlfwInput(GLFWwindow *window);

private:
};

#endif