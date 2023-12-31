#ifndef SCENE_H
#define SCENE_H

#pragma once
#include <event/event.h>
#include <camera/Camera.h>

class Window;

class Scene
{
public:
    Window *window;

    Camera *camera;

    Scene();
    ~Scene();

    virtual void render() = 0;

    virtual void onMouseEvent(MouseEvent *mouseEvent) {}

private:
};

#endif