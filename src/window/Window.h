#ifndef WINDOW_H
#define WINDOW_H

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <scene/Scene.h>
#include <event/event.h>
#include <map>
#include <string>

typedef void (*RenderFunc)();

class Window
{
public:
    GLFWwindow *glfwWindow;

    std::string title;

    int width;

    int height;

    Scene *currentScene;

    RenderFunc onRender;

    std::map<std::string, Scene *> scenes;

    Window(std::string title, int width, int height);

    ~Window();

    void render();

    void addScene(std::string sceneTitle, Scene *scene);

    void onMouseEvent(MouseEvent* mouseEvent);

private:
};

#endif