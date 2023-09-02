#ifndef SCENE_H
#define SCENE_H

#pragma once
#include <event/event.h>

class Scene
{
public:
    Scene();
    ~Scene();

    virtual void render() = 0;
    
    virtual void onMouseEvent(MouseEvent* mouseEvent) {}
private:
};

#endif